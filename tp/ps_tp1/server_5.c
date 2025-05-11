/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_5.c
 * cc -o server_5 server_5.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>     // Pour open()
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>     // Pour errno
#include <time.h>      // Pour srand() et rand()
#include <poll.h>      // Pour la fonction poll()

volatile bool running = true; // Variable globale
const char *fifo_path = "/tmp/my_fifo"; // Chemin vers la FIFO
int fifo_fd = -1; // File descriptor pour la FIFO initialisé à -1 indiquant non ouvert 

// Gestion des signaux pour terminer le programme
void handle_signal(int sig) {
    printf("Signal reçu : %s (%d)\n", strsignal(sig), sig);
    running = false;

    // Fermer proprement la FIFO si elle est ouverte
    if (fifo_fd != -1) {
        close(fifo_fd);
        fifo_fd = -1;
    }
    unlink(fifo_path); // Supprimer la FIFO
}

void message_de_fin() {
    printf("Serveur : Fin du programme.\n");
}

int main() {
    // Enregistrer la fonction de fin
    if (atexit(message_de_fin) != 0) {
        perror("Erreur lors de l'enregistrement de atexit");
        exit(EXIT_FAILURE);
    }

    // Configuration des signaux
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    
    //Gérer les cas d'erreurs
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Erreur lors de l'installation du gestionnaire SIGINT");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Erreur lors de l'installation du gestionnaire SIGTERM");
        exit(EXIT_FAILURE);
    }

    // Crée un tube nommé FIFO si celui-ci n'existe pas
    // FIFO permet la communication entre le client et le serveur
    if (mkfifo(fifo_path, 0666) == -1 && errno != EEXIST) {
        perror("Erreur lors de la création de la FIFO");
        exit(EXIT_FAILURE);
    }

    // Ouvrir la FIFO en écriture (bloquante)
    do {
        fifo_fd = open(fifo_path, O_WRONLY);
        if (fifo_fd == -1 && errno == ENXIO) {
            // Pas de lecteur connecté, réessayer après un moment
            sleep(1);
        }
    } while (fifo_fd == -1 && running);

    if (fifo_fd == -1) {
        perror("Erreur lors de l'ouverture de la FIFO");
        unlink(fifo_path);
        exit(EXIT_FAILURE);
    }

    printf("Serveur : Envoi des nombres aléatoires au client...\n");
    
    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Utiliser poll() pour surveiller la fermeture de la FIFO par le client
    struct pollfd pfd;
    pfd.fd = fifo_fd;
    pfd.events = POLLERR | POLLHUP; // Flags supplémentaires pour assurer une meilleure gesiton côté server
    //POLLHUP -> client a fermé la FIFO
    //POLLERR -> erreur produite sur la FIFO 

    while (running) {
        // Vérifier si le client s'est déconnecté
        int poll_result = poll(&pfd, 1, 0);
        if (poll_result == -1) {
            perror("Erreur lors de l'utilisation de poll");
            break;
        } else if (poll_result > 0) {
            if (pfd.revents & (POLLERR | POLLHUP)) {
                printf("Serveur : Client déconnecté, arrêt du serveur.\n");
                break;
            }
        }

        int num = rand() % 100; // Générer un nombre aléatoire entre 0 et 99
        ssize_t write_bytes = write(fifo_fd, &num, sizeof(num));
        if (write_bytes == -1) {
            if (errno == EPIPE) {
                // Le client a fermé la FIFO
                printf("Serveur : Client arrêté, fermeture du programme.\n");
                break;
            } else {
                perror("Serveur : Erreur d'écriture dans la FIFO");
                break;
            }
        }
        sleep(1); 
    }

    close(fifo_fd); // Fermer la FIFO
    unlink(fifo_path); // Supprimer la FIFO
    return 0;
}

/*
Cas 1: Quand le serveur est arrêté (crtl C ou kill Pidserver): 

Terminal Server:
Serveur : Envoi des nombres aléatoires au client...
^CSignal reçu : Interrupt (2)
Serveur : Fin du programme.

Terminal client: 

Client : Lecture des nombres depuis le serveur...
Client : Reçu 27
Client : Reçu 65
Client : Reçu 23
Client : Serveur arrêté, fermeture du programme.
Client : Fin du programme.

On obtient bien l'arrêt du client en conséquence avec le message d'arrêt.

Cas 2: Quand nous avons le client qui est arrêté en premier (crtl C ou kill Pidclient):

Terminal client:
Client : Lecture des nombres depuis le serveur...
Client : Reçu 18
Client : Reçu 28
Client : Reçu 33
^CSignal reçu : Interrupt (2)
Client : Erreur de lecture dans la FIFO: Interrupted system call
Client : Fin du programme.

Terminal server:
Serveur : Envoi des nombres aléatoires au client...
Serveur : Client déconnecté, arrêt du serveur.
Serveur : Fin du programme.

Cas 3: Quand on kill-9 server ou client
Nous avons bine le message spécefique de l'autre indiquant la bonne fermeture */