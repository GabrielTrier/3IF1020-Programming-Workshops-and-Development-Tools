/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°3
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * Arguments.cpp
 *
 * c++ -std=c++20 Arguments.cpp -o Arguments
 * ./Arguments
 */

#include <iostream>

// Passage par valeur
void f1( int i ) {
    int k = i;
    i = 3;
}

void g1() {
    f1( 5 );
    int j = 8;
    // j n'est pas modifié
    f1( j );
    f1( j + 2 );
    std::cout << "g1() : j = " << j << "\n";
}

// Passage par adresse
void f2( int * i ) {
    int k = *i;
    *i = 3;
}

void g2() {
    // f2( &5 );
    int j = 8;
    // f2( j );
    // j est modifié
    f2( &j );
    // f2( &( j + 2 ));
    std::cout << "g2() : j = " << j << "\n";
}

// Passage par référence sur valeur gauche
void f3( int & i ) {
    int k{ i };
    i = 3;
}

void g3() {
    // f3( 5 );
    int j{ 8 };
    // j est modifié
    f3( j );
    // f3( j + 2 );
    std::cout << "g3() : j = " << j << "\n";
}

// Passage par référence constante sur valeur gauche
void f4( const int & i ) {
    int k{ i };
    // i = 3;
}

void g4() {
    f4( 5 );
    int j{ 8 };
    // j n'est pas modifié
    f4( j );
    f4( j + 2 );
    std::cout << "g4() : j = " << j << "\n";
}


int main()
{
    g1();
    g2();
    g3();
    g4();
}
