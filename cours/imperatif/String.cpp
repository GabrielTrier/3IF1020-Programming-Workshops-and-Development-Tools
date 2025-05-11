/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°2
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * String.cpp
 *
 * Compilation :
 *      c++ -std=c++20 String.cpp -o String
 * Exécution :
 *      ./String
 */

#include <iostream>
#include <ios>
#include <string>
#include <cstring>

int main()
{
    // C : tableau de caractères avec une sentinelle
    char s1[] = "hello";
    // Taille du tableau : 5 caractères + la sentinelle '\0'
    std::cout << "sizeof( s1 ) = " << sizeof( s1 ) << "\n";
    // Taille de la chaîne de caractères : la sentinelle n'est pas comptée
    std::cout << "std::strlen( s1 ) = " << std::strlen( s1 ) << "\n";
    const char * s2 = "hello" ;
    // Taille du pointeur
    std::cout << "sizeof( s2 ) = " << sizeof( s2 ) << "\n";
    // Taille de la chaîne de caractères
    std::cout << "std::strlen( s2 ) = " << std::strlen( s2 ) << "\n";

    // Affichage de true/false plutôt que 1/0
    std::cout << std::boolalpha;
    // Comparaison de pointeurs, pas des chaînes
    std::cout << "s1 == s2 = " <<  ( s1 == s2 ) << "\n";
    // Comparaison des chaînes : 0 signifie chaînes identiques
    std::cout << "std::strcmp( s1, s2 ) = " <<  std::strcmp( s1, s2 ) << "\n";
    
    std::string s3{ "hello" };
    // Une string C++ se compare bien, y compris avec une
    // chaîne de caractères C
    std::cout << "s1 == s3 = " << ( s1 == s3 ) << "\n";
    // Concaténation
    std::string s4{ " world" };
    std::cout << "s3 + s4 = " << s3 + s4 << "\n";
    s3 += s4;
    std::cout << "s3 = " << s3 << "\n";
}
