/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°2
 * Dominique Marcadet - 2023 - CC BY-SA
 *
 * BasicTypes.cpp
 *
 * Compilation :
 *      c++ -std=c++20 BasicTypes.cpp -o BasicTypes
 * Exécution :
 *      ./BasicTypes
 */

#include <cstdint>
#include <iostream>
#include <limits>
#include <string>

// Une macro avec argument est nécessaire pour récupérer le nom du type
#define PRINT_INFO_ABOUT( T ) print_info_about< T >( #T )

// Une fonction générique affichant des informations sur un type
template< typename T >
void print_info_about( std::string type_name )
{
    std::cout << "sizeof( " << type_name << " ) = " << sizeof( T ) << "\n";
    // Le + permet qu'un char soit affiché comme un nombre et non comme un caractère
    std::cout << "min( "    << type_name << " ) = " << +std::numeric_limits< T >::min() << "\n";
    std::cout << "max( "    << type_name << " ) = " << +std::numeric_limits< T >::max() << "\n";
    // Pour afficher d'autres informations : voir https://en.cppreference.com/w/cpp/types/numeric_limits
    std::cout << "\n";
}


int main()
{
    // un char peut être signé ou pas
    PRINT_INFO_ABOUT(          char );
    PRINT_INFO_ABOUT(   signed char );
    PRINT_INFO_ABOUT( unsigned char );
    // Les autres entiers sont signés par défaut, donc le mot clef signed n'est pas obligatoire
    PRINT_INFO_ABOUT(   signed short );
    PRINT_INFO_ABOUT( unsigned short );
    PRINT_INFO_ABOUT(   signed int );
    PRINT_INFO_ABOUT( unsigned int );
    PRINT_INFO_ABOUT(   signed long );
    PRINT_INFO_ABOUT( unsigned long );
    PRINT_INFO_ABOUT(   signed long long );
    PRINT_INFO_ABOUT( unsigned long long );
    
    PRINT_INFO_ABOUT( float );
    PRINT_INFO_ABOUT( double );
    PRINT_INFO_ABOUT( long double );
    
    PRINT_INFO_ABOUT( bool );
}
