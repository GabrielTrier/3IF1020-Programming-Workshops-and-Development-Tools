/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système
 * Dominique Marcadet - 2023 - CC BY-SA
 *
 * Pipe.c
 *
 * Compilation :
 *     cc -o Pipe Pipe.c
 * Exécution :
 *     ./Pipe
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define HELLO "hello"

int main( int argc, char ** argv )
{
    // Tableau pour 2 descripteurs de fichier
    int fds[2];
    // Création d'un pipe, les bouts sont stockés dans fd
    if( pipe( fds ) == -1 ) {
        perror( "read" );
        return EXIT_FAILURE;
    }
    pid_t pid = fork();
    if( pid == -1 ) {
        perror( "fork" );
        return EXIT_FAILURE;
    }
    
    if( pid == 0 ) {      // Processus fils
        printf( "child\n" );
        close( fds[0] );  // Fermeture du côté lecture
        if( write( fds[1], HELLO, sizeof( HELLO )) == -1 ) {
            perror( "write" );
            return EXIT_FAILURE;
        }
    } else {              // Processus père
        printf( "parent\n" );
        close( fds[1] );  // Fermeture du côté écriture
        // on raccroche stdin au côté lecture du pipe
        if( dup2( fds[0], STDIN_FILENO ) == -1 ) {
            perror( "dup2" );
            return EXIT_FAILURE;
        }
        
        char buf[10];
        if( read( STDIN_FILENO, buf, sizeof( HELLO )) == -1 ) {
            perror( "read" );
            return EXIT_FAILURE;
        }
        else {
            printf( "stdin got %s\n", buf );
        }
        if( read( fds[0], buf, sizeof( HELLO )) == -1 ) {
            perror( "read" );
        }
        else {
            printf( "pipe got %s\n", buf );
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

