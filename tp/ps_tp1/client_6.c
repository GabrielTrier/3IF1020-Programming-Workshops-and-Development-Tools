/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * client_6.c
 * cc -o client_6 client_6.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <arpa/inet.h>  // Pour les fonctions réseau (htonl, htons)
#include <sys/socket.h> // Pour socket(), connect()

#define SERVER_IP "127.0.0.1" // Adresse loopback
#define PORT 8080 // Port devenant correspondre avec celui du server pour la communication

volatile bool running = true; 

// Gestion des signaux pour terminer le programme
void handle_signal(int sig) {
    printf("Signal reçu : %s (%d)\n", strsignal(sig), sig);
    running = false;
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
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    // Création du socket client
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    // Configurer l'adresse du serveur
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);  // Conversion du port en format réseau

    // Conversion de l'adresse IP du serveur en format binaire
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Erreur lors de la conversion de l'adresse IP");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Se connecter au serveur
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Erreur lors de la connexion au serveur");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client : Connecté au serveur, lecture des nombres...\n");
    int num;

    // Lire les nombres envoyés par le serveur
    while (running) {
        ssize_t read_bytes = read(client_fd, &num, sizeof(num));
        if (read_bytes > 0) {
            printf("Client : Reçu %d\n", num);
        } else if (read_bytes == 0) {
            // Le serveur a fermé la connexion
            printf("Client : Serveur arrêté, fermeture du programme.\n");
            break;
        } else {
            perror("Client : Erreur de lecture dans le socket");
            break;
        }
    }

    // Fermer le socket
    close(client_fd);
    return 0;
}

/* Explicaiton fourni dans le code server_6!
*/
