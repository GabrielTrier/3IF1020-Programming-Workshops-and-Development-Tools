/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_6.c
 * cc -o server_6 server_6.c
 */

#include <errno.h>     // Pour errno
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <arpa/inet.h>  // Pour les fonctions réseau (htonl, htons)
#include <sys/socket.h> // Pour socket(), bind(), listen(), accept()
#include <time.h>       // Pour générer des nombres aléatoires
#include <poll.h>       // Pour la fonction poll()

#define PORT 8080       // Port choisi pour le serveur

volatile bool running = true; // Variable globale
int server_fd = -1; // Socket pas encore ouvert
int client_fd = -1; // Indiquant que la connexion est non établie

// Gestion des signaux pour terminer le programme
void handle_signal(int sig) {
    printf("Signal reçu : %s (%d)\n", strsignal(sig), sig);
    running = false;

    // Fermer proprement le client et server (si ouvert)
    if (client_fd != -1) {
        shutdown(client_fd, SHUT_RDWR);
        close(client_fd);
        client_fd = -1;
    }

    if (server_fd != -1) {
        shutdown(server_fd, SHUT_RDWR);
        close(server_fd);
        server_fd = -1;
    }
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
    
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Erreur lors de l'installation du gestionnaire SIGINT");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Erreur lors de l'installation du gestionnaire SIGTERM");
        exit(EXIT_FAILURE);
    }

    // Création du socket serveur
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    // Activer les options SO_REUSEADDR et SO_REUSEPORT pour pouvoir réutiliser le port immédiatement (sinon temps de latence)
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("Erreur lors de la configuration de SO_REUSEADDR");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
        perror("Erreur lors de la configuration de SO_REUSEPORT");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Configurer l'adresse du serveur (IPv4, port)
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET; // Domaine IPv4
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Toutes les interfaces locales sont converties en format réseau
    server_addr.sin_port = htons(PORT); // Conversion du port en format réseau

    // Associer l'adresse et le socket avec bind()
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Erreur lors de l'association");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Ecouter les connexions entrantes avec listen()
    if (listen(server_fd, 1) == -1) {
        perror("Erreur lors de l'écoute");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Serveur : En attente de connexion sur le port %d...\n", PORT);

    // Accepter une connexion entrante
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_fd == -1) {
        perror("Erreur lors de l'acceptation");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Serveur : Connexion acceptée, envoi des nombres aléatoires au client...\n");

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Utiliser poll() pour surveiller les événements sur le socket client
    // La focntion permet au serveur de détecter rapidement la déconnexion du client assurant ainsi un arrêt propre
    struct pollfd pfd;
    pfd.fd = client_fd;
    pfd.events = POLLHUP | POLLERR | POLLNVAL;

    // Envoi des nombres aléatoires au client
    while (running) {
        // Vérifier les événements sur le socket
        int poll_result = poll(&pfd, 1, 0);
        if (poll_result == -1) {
            perror("Erreur lors de l'utilisation de poll");
            break;
        } else if (poll_result > 0) {
            if (pfd.revents & (POLLHUP | POLLERR | POLLNVAL)) {
                printf("Serveur : Le client s'est déconnecté, arrêt du serveur.\n");
                running = false;
                break;
            }
        }

        // Envoyer un nombre aléatoire au client
        int random_number = rand() % 100; // Générer un nombre aléatoire entre 0 et 99
        ssize_t write_bytes = write(client_fd, &random_number, sizeof(random_number));
        if (write_bytes == -1) {
            if (errno == EPIPE) {
                // Le client a fermé la connexion
                printf("Serveur : Le client s'est déconnecté, arrêt du serveur.\n");
                running = false;  // Arrêter le serveur lorsque le client se déconnecte
                break;
            } else {
                perror("Serveur : Erreur d'écriture dans le socket");
                break;
            }
        }
        sleep(1); 
    }
    return 0;
}
/* On observe que pour tout le scas de figure, que le client et le server s'arrêtent bien en affichant leurs messages!
Pour chacun des cas le server démarre dans un premier temps et attend la connexion client:

Serveur : En attente de connexion sur le port 8080...

Une fois que le client se connecte au serveur, le server peut envoyer les nombres et le client peut les lire:
Client : Connecté au serveur, lecture des nombres...
Serveur : Connexion acceptée, envoi des nombres aléatoires au client...

Le client reçoit des nombres :
Client : Reçu 20 (exemple)

Cas 1 : Arrêt du client (via Ctrl+C ou kill)

Signal reçu : Interrupt (2)
Client : Fin du programme.

Le serveur détecte la déconnexion du client et s'arrête :
Serveur : Le client s'est déconnecté, arrêt du serveur.
Serveur : Fin du programme.

Cas 2 : Arrêt du serveur (via Ctrl+C ou kill)

Signal reçu : Interrupt (2)
Serveur : Fin du programme.

Le client détecte la fermeture de la connexion par le serveur :
Client : Serveur arrêté, fermeture du programme.
Client : Fin du programme.

Cas 3 : Arrêt du serveur avec kill -9

Aucun message d'arrêt n'est affiché par le serveur, car kill -9 ne permet aucune exécution de code de nettoyage.

Cependant, le client détecte que la connexion est fermée :
Client : Serveur arrêté, fermeture du programme.
Client : Fin du programme.

*/