/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°1
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * HelloWorld.c
 *
 * Compilation, l'exécutable se nommera a.out (ou a.exe sur Windows) :
 *     cc HelloWorld.c
 * Exécution :
 *     ./a.out
 *
 * Compilation en choisissant le nom de l'exécutable :
 *     cc -o HelloWorld HelloWorld.c
 * Exécution :
 *     ./HelloWorld
 */

// Fichier d'entête déclarant la fonction printf()
#include <stdio.h>

// main() est la fonction principale, le point d'entrée du programme
int main()
{
    // printf() est la fonction C d'affichage sur la sortie standard
    printf( "hello world\n" );
    // Le code retourné par main() indique au système d'exploitation si l'exécution 
    // s'est bien passée (0) ou pas (toute autre valeur)
    return 0; 
}

