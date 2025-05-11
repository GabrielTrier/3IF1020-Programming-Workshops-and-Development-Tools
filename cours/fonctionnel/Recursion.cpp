/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°3
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * Recursion.cpp
 *
 * c++ -std=c++20 Recursion.cpp -o Recursion
 * ./Recursion
 */

#include <iostream>

/*
 * Pré-condition : tab doit contenir au moins un entier égal à 0
 */
int longueur_tableau_iteratif( int tab[] ) {
    int i = 0;
    while( tab[i] != 0 ) {
        i = i + 1;
    }
    return i;
}

int longueur_tableau_recursif( int tab[] ) {
    if( tab[0] == 0 ) {
        return 0;
    }
    return 1 + longueur_tableau_recursif( tab + 1 );
}

int main()
{
    int tab[] = { 1, 2, 3, 4, 5, 0 };
    std::cout << "longueur_tableau_iteratif( tab ) = " << longueur_tableau_iteratif( tab ) << "\n";
    std::cout << "longueur_tableau_recursif( tab ) = " << longueur_tableau_recursif( tab ) << "\n";
}
