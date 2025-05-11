/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°2
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * Pointer_1.cpp
 *
 * Compilation :
 *      c++ -std=c++20 Pointer_1.cpp -o Pointer_1
 * Exécution :
 *      ./Pointer_1
 */

#include <iostream>

int main()
{
    int i{ 5 };
    std::cout << " i = " << i  << "\n";
    // p pointe sur i
    int * p{ &i };
    // *p est la même donnée que i
    std::cout << "*p = " << *p << "\n";
    // Afficher un pointeur revient à afficher l'adresse de la variable pointée
    std::cout << " p = " << p  << "\n";
    
    std::cout << "Affectation de -7 dans *p\n";
    *p = -7;
    // Affichage de la même donnée accédée par i
    std::cout << " i = " << i  << "\n";
    std::cout << "*p = " << *p << "\n";
    std::cout << " p = " << p  << "\n";
    
    int j{ 100 };
    std::cout << "Affectation de &j dans p\n";
    p = &j;
    *p += 1;
    // i a conservé sa valeur
    std::cout << " i = " << i  << "\n";
    // j et *p sont maintenant la même donnée
    std::cout << " j = " << j  << "\n";
    std::cout << "*p = " << *p << "\n";
    // L'adresse contenue dans p a changé
    std::cout << " p = " << p  << "\n";
}
