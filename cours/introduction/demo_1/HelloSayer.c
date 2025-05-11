/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°1
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * HelloSayer.c
 *
 * Compilation :
 *     cc -o HelloSayer HelloSayer.c
 * Exécution :
 *     ./HelloSayer World
 */

#include <stdio.h>

// Définition d'une fonction qui reçoit un tableau de caractères comme paramètre
void hello( char world[] )
{
    printf( "Hello %s\n", world );
}

// La fonction principale reçoit en paramètres le nombre d'arguments de la ligne de
// commande et ces arguments sous la forme d'un tableau de chaînes de caractères
int main( int argc, char * argv[] )
{
    // argv[0] est le nom de l'exécutable
    // argv[1] est le premier argument sur la ligne de commande
    // Appel de la fonction hello() avec un argument
    if( argc > 1 ) hello( argv[1] );
    return 0;
}
