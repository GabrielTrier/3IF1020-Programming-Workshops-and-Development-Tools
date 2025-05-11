/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système
 * Dominique Marcadet - 2023 - CC BY-SA
 *
 * Fork.c
 *
 * Compilation :
 *     cc -o Fork Fork.c
 * Exécution :
 *     ./Fork
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char ** argv )
{
    printf( "%s with pid = %d started\n", argv[0], getpid() );
    
    if( argc > 1 ) {
        printf( "argument on command line is %s\n", argv[1] );
    }
    else {
        printf( "no argument on command line\ncalling fork()\n" );
        pid_t pid = fork();
        if( pid == -1 ) {
            perror( "fork" );
            return EXIT_FAILURE;
        }
        
        if( pid == 0 ) {
            printf( "this is the child process, my pid is %d\n", getpid() );
            printf( "I will launch the same process with an argument\n" );
            if( execl( argv[0], argv[0], "HelloWorld", (char *) NULL ) == -1 ) {
                perror( "execl" );
                return EXIT_FAILURE;
            }
        }
        else {
            printf( "this is the parent process, my child's pid is %d\n", pid );
        }
    }
    
    printf( "%s with pid = %d finished\n", argv[0], getpid() );
    return EXIT_SUCCESS;
}
