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
#include <string.h>
// Pour waitpid()
#include <sys/wait.h> 

// Variable globale
volatile bool running = true;
pid_t child_pid = -1; // Pour garder la trace du processus fils

// Fonction de gestion des signaux
void handle_signal(int sig) {
    printf("Signal reçu : %s (%d)\n", strsignal(sig), sig);
    if (child_pid > 0) { // Si le père reçoit le signal, il arrête le fils
        printf("Père : Arrêt du fils (PID %d) avant de s'arrêter.\n", child_pid);
        kill(child_pid, SIGTERM); // Envoi SIGTERM au fils
        waitpid(child_pid, NULL, 0); // On attend que le fils se termine
    }
    printf("Arrêt du programme demandé par signal!\n");
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

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Erreur lors de l'installation de sigaction pour SIGINT");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Erreur lors de l'installation de sigaction pour SIGTERM");
        exit(EXIT_FAILURE);
    }

    printf("Bonjour, le programme démarre!\n");

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Duplication du processus avec fork()
    child_pid = fork();

    if (child_pid < 0) { // Cas erreur de fork
        perror("Erreur lors de la duplication du processus");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Cas processus fils
        while (running) {
            printf("Fils - Process ID: %d, Parent ID: %d, Group ID: %d\n", getpid(), getppid(), getpgrp());
            printf("Fils - Nbr aléatoire: %d\n", rand() % 100);
            sleep(1);
        }
    } else { // Cas processus père
        while (running) {
            printf("Père - Process ID: %d, Parent ID: %d, Group ID: %d\n", getpid(), getppid(), getpgrp());
            printf("Père - Nbr aléatoire: %d\n", rand() % 100);
            sleep(1);

            // Vérifier si le fils s'est arrêté
            int status;
            pid_t result = waitpid(child_pid, &status, WNOHANG);
            if (result == child_pid) {
                printf("Père : Le fils (PID %d) s'est arrêté, le père s'arrête aussi.\n", child_pid);
                running = false;
            }
        }
    }

    return EXIT_SUCCESS;
}
/*
Le fils hérite de nombreux attributs du processus père, dont l'identifiant de groupe. 
On remarque que le numéro de groupe (Group ID) est le même pour les deux processus (père et fils) 
car le fils hérite de est créé comme une copie du processus père et partage le même groupe de processus.

Concrètement les deux processus s'arrètent avec crtl C car ils sont dans le mêle groupe.
*/


/*  Derière partie de la 2.1

1. Quand on tue le fils :
Le fils reçoit un signal (SIGTERM) et se termine.
Le père utilise waitpid() pour surveiller l'état du fils et quand le fils se termine, waitpid() le détecte.
Le père affiche donc un message indiquant que le fils est mort, puis il s'arrête aussi.

2. Quand on tue le père :
Le père reçoit un signal (SIGTERM) et envoie immédiatement un signal SIGTERM au fils.
Le père attend la fin du fils avec waitpid().
Une fois le fils mort, le père s'arrête.
*/