/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°1
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * InputOutput.c
 *
 * Compilation avec édition de liens :
 *     cc -o InputOutput InputOutput.c
 *
 * Exécution :
 *     ./InputOutput
 */

// Fichier d'entête de la bibliothèque standard d'entrées/sorties C
#include <stdio.h>

int main() {
    // stdout représente la sortie standard
    fprintf( stdout, "Donner un nombre : " );
    int n = 0;
    // stdin représente l'entrée standard
    // %d indique qu'un entier doit être lu
    int nb_parsed = fscanf( stdin, "%d", &n );
    // La valeur de retour de fscanf est le nombre de variables correctement lues
    if( nb_parsed == 1 ) {
        // %d indique qu'un entier doit être affiché
        fprintf( stdout, "Le carré de %d est %d\n", n, n * n );
    }
    return 0;
}
