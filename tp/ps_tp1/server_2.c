/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_2.c
 * cc -o server_2 server_2.c
 */

// Commencer par recopier ici le code de server_1.c
/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_2.c
 * cc -o server_2 server_2.c
 */

// Commencer par recopier ici le code de server_1.c
// Pour printf()
#include <stdio.h>
// Pour rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// Pour time()
#include <time.h>
// Pour getpid(), getppid()
#include <unistd.h>
// Pour gestion des signaux
#include <signal.h>
// Pour type boolean et true/false
#include <stdbool.h>

// Variable globale
volatile bool running = true;

// Fonction de gestion des signaux SIGINT et SIGTERM
void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("Signal reçu : %d\n", sig);
    } else if (sig == SIGTERM) {
        printf("Signal reçu : %d\n", sig);
    }
    printf("Arrêt du programme demandé par un signal.\n");
    running = false;
}

void message_de_fin() {
    printf("Le programme s'est terminé correctement!\n");
}

int main() {
    // Enregistrer la fonction à appeler à la fin du programme
    if (atexit(message_de_fin) != 0) {
        perror("Erreur lors de l'enregistrement de atexit");
        exit(EXIT_FAILURE);
    }

    // Configuration de sigaction pour gérer SIGINT et SIGTERM
    struct sigaction sa;
    sa.sa_handler = handle_signal; 
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);  

    // Installation de la fonction de gestion pour SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Erreur lors de l'installation de sigaction pour SIGINT");
        exit(EXIT_FAILURE);
    }
    // Installation de la fonction de gestion pour SIGTERM
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Erreur lors de l'installation de sigaction pour SIGTERM");
        exit(EXIT_FAILURE);
    }

    printf("Bonjour, le programme démarre!\n");
    while (running) {
        printf("Process ID: %d, Parent ID: %d, Group ID: %d\n", getpid(), getppid(), getpgrp());
        printf("Nombre aléatoire entre 0 et 99 : %d\n", rand() % 100);
        sleep(1); 
    }
    printf("Fin du programme.\n");
    return EXIT_SUCCESS;
}


/*
Process ID: 32066, Parent ID: 548, Group ID: 32066
Nombre aléatoire entre 0 et 99 : 92
^CSignal reçu : 2
Arrêt du programme.
Fin du programme.

Avec le flag -s INT numeroPID on observe que le message est bien affiché,
le signal SIGINT (signal 2) est donc traité par le programme.

Cependant sans le flag -s INT les messages ne sont pas affichés 
car la fonction de gestion du signal SIGINT ne traite pas ce numéro de signal.
*/

/*Lorsque on utilise la commande kill -9 <PID> on remarque que le message n'est pas affiché.
Cela est due au fait que le signal SIGKILL (signal 9) envoyé au processus contrairement à d'autres signaux comme SIGINT ou SIGTERM, SIGKILL ne peut pas être intercepté, ignoré, ou géré par un programme.
Des la récéption de ce signal le noyau arrête immédiatement le processus sans lui donner le temps d'exécuter une fonction de nettoyage ou d'afficher un message.
*/

