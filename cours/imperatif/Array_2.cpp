/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°2
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * Array_2.cpp
 *
 * Compilation :
 *      c++ -std=c++20 Array_2.cpp -o Array_2
 * Exécution :
 *      ./Array_2
 */

#include <iostream>
#include <vector>

using Tab = std::vector< int >;

// Un tableau C++ connait sa taille
void print_tab_1( Tab tab )
{
    std::cout << "[ ";
    // Parcours par indice
    for( unsigned i = 0; i < tab.size(); ++i ) {
        std::cout << tab[i] << " ";
    }
    std::cout << "]\n";
}

void print_tab_2( Tab tab )
{
    std::cout << "[ ";
    // Parcours par pointeur toujours possible
    // Mais pas de conversion implicite en pointeur sur le premier élément
    for( int * p = &tab[0]; p < &tab[0] + tab.size(); ++p ) {
        std::cout << *p << " ";
    }
    std::cout << "]\n";
}

int main()
{
    Tab tab_1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    // Un std::vector peut changer de taille, donc les éléments sont stockés
    // dans un bloc mémoire alloué dynamiquement
    // 1 pointeur et 2 entiers (taille du tableau, taille du bloc mémoire qui peut
    // être plus grand) sont mémorisés
    std::cout << "sizeof( tab_1 ) = " << sizeof( tab_1 ) << "\n";
    print_tab_1( tab_1 );
    print_tab_2( tab_1 );
    
    Tab tab_2 = tab_1;
    // tab_2 est un autre tableau
    tab_2[0] = 100;
    print_tab_1( tab_1 );
    print_tab_2( tab_2 );
    
    // Toujours pas de vérification d'indice
    std::cout << "tab_1[-1] = " << tab_1[-1] << "\n";
    std::cout << "tab_1[11] = " << tab_1[11] << "\n";
    
    // Sauf en utilisant cette notation
    // Un exception sera émise si vous décommentez cette ligne
    //std::cout << "tab_1.at( -1 ) = " << tab_1.at( -1 ) << "\n";
}
