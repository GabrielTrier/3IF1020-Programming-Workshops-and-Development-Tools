/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°1
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * HelloSayer.cpp
 *
 * Compilation :
 *     c++ -o HelloSayer HelloSayer.cpp
 * Exécution :
 *     ./HelloSayer World
 */

#include <cstdio>
#include <iostream>
#include <string>

// Il existe un type string en C++
void hello( std::string world )
{
    // Il est possible d'utiliser printf() en C++
    std::printf( "Hello %s\n", world.c_str() );
    
    // Mais il existe une bibliothèque d'entrées/sorties plus adaptée
    std::cout << "Hello " << world << std::endl;
}

// Comme en C
int main( int argc, char * argv[] )
{
    if( argc > 1 ) hello( argv[1] );
    return 0;
}
