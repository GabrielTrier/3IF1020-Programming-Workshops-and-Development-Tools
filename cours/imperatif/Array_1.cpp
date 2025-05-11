/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°2
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * Array_1.cpp
 *
 * Compilation :
 *      c++ -std=c++20 Array_1.cpp -o Array_1
 * Exécution :
 *      ./Array_1
 */

#include <iostream>

// Un tableau basique ne connait pas sa taille, elle est donc fournie
// comme paramètre
void print_tab_1( int tab[], unsigned size )
{
    std::cout << "[ ";
    // Parcours par indice
    for( unsigned i = 0; i < size; ++i ) {
        std::cout << tab[i] << " ";
    }
    std::cout << "]\n";
}

// Typer le paramètre tab comme pointeur ne change rien
void print_tab_2( int * tab, unsigned size )
{
    std::cout << "[ ";
    // Parcours par pointeur
    for( int * p = tab; p < tab + size; ++p ) {
        std::cout << *p << " ";
    }
    std::cout << "]\n";
}

int main()
{
    int tab_1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    // Pour un tableau initialisé ainsi, sizeof( tab_1 ) est bien 
    // la taille de l'ensemble du tableau
    std::cout << "sizeof( tab_1 ) = " << sizeof( tab_1 ) << "\n";
    print_tab_1( tab_1, sizeof( tab_1 ) / sizeof( tab_1[0] ));
    // tab1 est converti en pointeur sur le premier élément, donc *tab1 est le premier élément
    print_tab_2( tab_1, sizeof( tab_1 ) / sizeof( *tab_1 ));
    
    const unsigned taille{ 10 };
    int * tab_2 = new int[taille];
    for( int i = 0; i < taille; ++i ) {
        tab_2[i] = tab_1[i] * 2;
    }
    // Ici, sizeof( tab_2 ) est la taille du pointeur, pas du tableau
    std::cout << "sizeof( tab_2 ) = " << sizeof( tab_2 ) << "\n";
    print_tab_1( tab_2, taille );
    // Pour un tableau alloué dynamiquement, le standard impose d'utiliser
    // cette version de delete pour la libération
    delete[] tab_2;
    
    // Pas de vérification d'indice à l'exécution (mais avertissements à la compilation)
    // Le comportement est réputé indéterminé et le programme non conforme
    std::cout << "tab_1[-1] = " << tab_1[-1] << "\n";
    std::cout << "tab_1[11] = " << tab_1[11] << "\n";
}
