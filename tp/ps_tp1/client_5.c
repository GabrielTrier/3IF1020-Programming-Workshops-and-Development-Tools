/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * client_5.c
 * cc -o client_5 client_5.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>     // Pour open()
#include <stdbool.h>
#include <string.h>

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
}

void message_de_fin() {
    printf("Client : Fin du programme.\n");
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

    // Ouvrir la FIFO en lecture bloquante
    fifo_fd = open(fifo_path, O_RDONLY);
    if (fifo_fd == -1) {
        perror("Erreur lors de l'ouverture de la FIFO");
        exit(EXIT_FAILURE);
    }

    printf("Client : Lecture des nombres depuis le serveur...\n");
    int num;

    while (running) {
        ssize_t read_bytes = read(fifo_fd, &num, sizeof(num));
        if (read_bytes > 0) {
            printf("Client : Reçu %d\n", num);
        } else if (read_bytes == 0) {
            // Le serveur a fermé la FIFO
            printf("Client : Serveur arrêté, fermeture du programme.\n");
            break;
        } else {
            perror("Client : Erreur de lecture dans la FIFO");
            break;
        }
    }

    close(fifo_fd); // Fermer la FIFO
    return 0;
}
