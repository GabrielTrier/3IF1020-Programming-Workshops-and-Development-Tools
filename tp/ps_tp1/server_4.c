/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_4.c
 * cc -o server_4 server_4.c
 */

// Commencer par recopier ici le code de server_3.c
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

volatile bool running = true;
pid_t child_pid = -1;
int pipe_fd[2];

// Fonction de gestion des signaux
void handle_signal(int sig) {
    printf("Signal reçu : %s (%d)\n", strsignal(sig), sig);
    running = false;
    close(pipe_fd[0]); // Fermer l'extrémité lecture
    close(pipe_fd[1]); // Fermer l'extrémité écriture
}

void parent_process() {
    close(pipe_fd[0]); // Fermer l'extrémité lecture du père
    int num = 0;
    while (running) {
        // Attendre la fin du fils sans bloquer l'exécution
        if (waitpid(child_pid, NULL, WNOHANG) == child_pid) {
            printf("Père : Le fils est mort, arrêt de l'écriture.\n");
            break;
        }
        
        ssize_t write_bytes = write(pipe_fd[1], &num, sizeof(num));
        if (write_bytes == -1) {
            perror("Père : Erreur d'écriture dans le tube");
            break; // Sortir de la boucle si erreur d'écriture détectée
        }
        num++;
        sleep(1); // Attente d'une seconde entre chaque écriture
    }
    close(pipe_fd[1]); // Fermer l'extrémité écriture lorsque le père se termine
    wait(NULL); // Attendre la fin du fils
    printf("Père : Fin du programme.\n");
}

void child_process() {
    close(pipe_fd[1]); // Fermer l'extrémité écriture du fils
    int num;
    while (running) {
        ssize_t read_bytes = read(pipe_fd[0], &num, sizeof(num));
        if (read_bytes > 0) {
            printf("Fils : Reçu %d\n", num);
        } else if (read_bytes == 0) {
            // Le tube a été fermé par le père
            printf("Fils : Tube fermé, arrêt du programme.\n");
            break;
        } else {
            perror("Fils : Erreur de lecture dans le tube");
            break;
        }
    }
    close(pipe_fd[0]); // Fermer l'extrémité lecture lorsque le fils se termine
    printf("Fils : Fin du programme.\n");
}

int main() {

    printf("Bonjour, le programme démarre!\n");

    // Configuration des signaux
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    // Création du tube
    if (pipe(pipe_fd) == -1) {
        perror("Erreur lors de la création du tube");
        exit(EXIT_FAILURE);
    }

    // Création du processus fils
    child_pid = fork();
    if (child_pid == -1) {
        perror("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);
    }

    if (child_pid > 0) {
        parent_process(); // Exécution du processus père
    } else {
        child_process(); // Exécution du processus fils
    }
    return 0;
}
/* Quand le fils est tué, nous avons bien le message du père qui s'affiche:
Signal reçu : Terminated (15)
Fils : Erreur de lecture dans le tube: Bad file descriptor
Fils : Fin du programme.
Père : Le fils est mort, arrêt de l'écriture.
Père : Fin du programme.

Dans le cas ou le père est tué en premier:

Signal reçu : Terminated (15)
Fils : Tube fermé, arrêt du programme.
Fils : Fin du programme.
Père : Fin du programme.

Cas d'un arrêt forcé avec crtl C:

^CSignal reçu : Interrupt (2)
Signal reçu : Interrupt (2)
Fils : Erreur de lecture dans le tube: Bad file descriptor
Fils : Fin du programme.
Père : Fin du programme.*/