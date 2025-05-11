/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique - Campus de Paris-Saclay
 * 3IF1020 – Ateliers de programmation et outils de développement - TD n°2
 * https://wdi.centralesupelec.fr/3IF1020/ProgTD2
 *
 * c++ -std=c++20 -o td2 td2.cpp
 * ./td2
 * valgrind ./td2
 */


#include <iostream>
#include <iomanip>
#include <cctype>
#include <cassert>
#include <cmath>
#include <limits>


// Définir DigitType comme type de l'attribut stockant le chiffre ; nous utiliserons pour
// commencer un unsigned short.
// TODO

// Définir un agrégat Digit permettant de stocker un chiffre entre 0 et 9 (donc de type
// DigitType) et un pointeur vers le chiffre suivant.
// TODO

// Définir le type Number comme pointeur sur un Digit.
// TODO

// Définir 10 sous forme de constante nommée number_base, de type DigitType, vous utiliserez
// cette constante dans votre code chaque fois qu'il s'agira de tenir compte du fait qu'un
// chiffre stocké dans un Digit est compris entre 0 et 9.
// TODO

// Écrire une fonction affichant un nombre (sans retour à la ligne après)
// void print_number( Number n );
// {
//    // TODO
// }

// Définir une fonction test_31() qui construit le nombre 123 et l'affiche. 
void test_31()
{
    std::cout << "test_31: TODO\n";
}

// Écrire une fonction libérant la mémoire utilisée pour représenter un nombre
// void free_number( Number n )
// {
//     // TODO
// }

// Définir une fonction test_32() qui construit le nombre 123 en utilisant de l'allocation
// dynamique pour les agrégats, l'affiche puis libère la mémoire qui a été allouée. 
void test_32()
{
    std::cout << "test_32: TODO\n";
}

// Écrire une fonction retournant un nombre construit à partir de l'argument reçu
// Number build_number( unsigned long l )
// {
//     // TODO
// }

// Définir une fonction test_33() qui lit un entier fourni par l'utilisateur, construit
// le nombre correspondant, l'affiche puis libère la mémoire qui a été allouée.
void test_33()
{
    std::cout << "test_33: TODO\n";
}

// Écrire une fonction retournant un nombre construit à partir des chiffres lus sur
// l'entrée standard
// Number read_number()
// {
//     // TODO
//     return nullptr;
// }

// Définir une fonction test_34() qui lit un nombre fourni par l'utilisateur, l'affiche
// puis libère la mémoire qui a été allouée.
void test_34()
{
    std::cout << "test_34: TODO\n";
}

// Écrire une fonction multipliant un nombre par un entier
// void multiply_number( Number n, unsigned long l, unsigned long carry = 0 )
// {
//     // TODO
// }

// Définir une fonction test_41() qui lit un nombre fourni par l'utilisateur, puis un
// entier, affiche le résultat de la multiplication du nombre par l'entier puis libère
// la mémoire qui a été allouée
void test_41()
{
    std::cout << "test_41: TODO\n";
}

// Écrire une fonction calculant la factorielle d'un entier
// Number factorial( unsigned long l )
// {
//     // TODO
//     return nullptr;
// }

// Définir une fonction test_42() qui lit un entier fourni par l'utilisateur, affiche sa
// factorielle puis libère la mémoire qui a été allouée
void test_42()
{
    std::cout << "test_42: TODO\n";
}

// Définir une fonction test_51() qui crée un nombre de valeur number_base - 1 et appelle
// la fonction multiply_number() avec ce nombre comme premier argument et
// std::numeric_limits< unsigned long >::max() (qui vaut 0xFFFFFFFFFFFFFFFFu pour un
// unsigned long de 64 bits) comme second argument (il faut inclure <limits>). Afficher
// ensuite le nombre.
void test_51()
{
    std::cout << "test_51: TODO\n";
}

// Définir une fonction test_52() qui affiche la factorielle d'un argument donné sur la
// ligne de commande, puis libère la mémoire qui a été allouée.
void test_52( unsigned int i )
{
    std::cout << "test_52: TODO\n";
}

// Définir une fonction test_53() qui affiche la factorielle d'un entier choisi pour que
// le temps de calcul nécessaire soit d'environ 10s, puis libère la mémoire qui a été allouée. 
void test_53()
{
    std::cout << "test_53: TODO\n";
}

/*
// c++ -std=c++20 -O3 -o td2 td2.cpp -lgmp

#include <boost/multiprecision/gmp.hpp>

boost::multiprecision::mpz_int factorial_gmp( unsigned long l )
{
    if( l <= 0 ) return 1;
    boost::multiprecision::mpz_int n{ l };
    while( --l > 0 ) n *= l;
    return n;
}

void test_6()
{
    unsigned long l{ 500000 };
    boost::multiprecision::mpz_int v { factorial_gmp( l )};
    std::cout << v << "\n";
}
*/

int main( int argc, char * argv[] )
{
    test_31();
    test_32();
    test_33();
    test_34();
    test_41();
    test_42();
    test_51();
    if( argc > 1 ) {
        unsigned int n{ static_cast< unsigned int >( std::stoul( argv[1] ))};
        test_52( n );
    }
    else {
        std::cout << "Donner un nombre sur la ligne de commande\n";
    }
    test_53();
}
