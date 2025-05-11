/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°5
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * Factorial.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o Factorial Factorial.cpp
 *     c++ -std=c++20 -S Factorial.cpp
 *     c++ -std=c++20 -O3 -S Factorial.cpp
 * Exécution :
 *     ./Factorial
 */

#include <iostream>
#include <cstdlib>

#define USE_TEMPLATE

#ifdef USE_TEMPLATE

template< unsigned N >
struct Factorial {
    static constexpr unsigned value{
	         N * Factorial< N-1 >::value };
};

template<>
struct Factorial< 0 > {
    static constexpr unsigned value{ 1 };
};

#else

constexpr unsigned factorial( unsigned value )
//consteval unsigned factorial( unsigned value )
{
    if( value <= 1 ) return 1;
    return value * factorial( value - 1 );
}

#endif

int main()
{
    unsigned i{ std::rand() % 10u };
#ifdef USE_TEMPLATE
    std::cout << "Factorial< 0 >  = " << Factorial< 0  >::value << "\n";
    std::cout << "Factorial< 13 > = " << Factorial< 13 >::value << "\n";
    std::cout << "Factorial< 14 > = " << Factorial< 14 >::value << "\n";
    //std::cout << "Factorial< " << i << " > = " << Factorial< i >::value << "\n";
#else
    std::cout << "factorial( 0 )  = " << factorial( 0 )  << "\n";
    std::cout << "factorial( 13 ) = " << factorial( 13 ) << "\n";
    std::cout << "factorial( 14 ) = " << factorial( 14 ) << "\n";
    std::cout << "factorial( " << i << " ) = " << factorial( i ) << "\n";
#endif
}

