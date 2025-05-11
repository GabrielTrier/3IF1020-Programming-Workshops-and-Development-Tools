/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_1.c
 * cc -o server_1 server_1.c
 */

// for printf()
#include <stdio.h>
// For rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// For time()
#include <time.h>
// For getpid(), getppid()
#include <unistd.h>

int main()
{
    //
    printf("Bonjour, le programme démarre!\n");
    while (1)
    {   
        printf("Process ID: %d, Parent ID: %d, Group ID: %d\n", getpid(), getppid(), getpgrp());
        printf("Nombre aléatoire entre 0 et 99 : %d\n", rand() % 100); 
        sleep(1);
    }
    // Ce message ne sera jamais atteint à cause de la boucle infinie
    printf("Fin du programme.\n");   
    return EXIT_SUCCESS;
}

/* Sorti du terminal 1
Bonjour, le programme démarre!
Process ID: 25202, Parent ID: 548, Group ID: 25202
Nombre aléatoire entre 0 et 99 : 83
Process ID: 25202, Parent ID: 548, Group ID: 25202
Nombre aléatoire entre 0 et 99 : 86
Process ID: 25202, Parent ID: 548, Group ID: 25202
Nombre aléatoire entre 0 et 99 : 77

Sorti du terminal avec ps aj:
PPID     PID    PGID     SID TTY        TPGID STAT   UID   TIME COMMAND
    531     548     548     548 pts/0      25202 Ss     911   0:02 /bin/zsh -i
    531     568     568     568 pts/1      25280 Ss     911   0:01 /bin/zsh -i
    548   25202   25202     548 pts/0      25202 S+     911   0:00 ./server_1
    568   25280   25280     568 pts/1      25280 R+     911   0:00 ps aj

On remarque que le processus server_1 d'iD (25202) a été lancé par le shell zsh (PID 548), qui est son processus père (visible grâce au PPID).
De plus, on observe que le processus server_1 est le leader de son propre groupe de processus avec un PGID de 25202 qui est le même que son PID.
*/

/* En tuant le process avec la commande kill 27854 (id de mon process), on remarque bien que le process est interrompu:
Process ID: 27854, Parent ID: 548, Group ID: 27854
Nombre aléatoire entre 0 et 99 : 67
[1]    27854 terminated  ./server_1
*/

