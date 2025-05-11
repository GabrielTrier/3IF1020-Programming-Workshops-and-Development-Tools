/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°2
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * Pointer_2.cpp
 *
 * Compilation :
 *      c++ -std=c++20 Pointer_2.cpp -o Pointer_2
 * Exécution :
 *      ./Pointer_2
 */

#include <iostream>

int main()
{
    int i{ 5 };
    std::cout << " i = " << i  << "\n";
    int * p{ &i };
    std::cout << " p = " << p  << "\n";
    std::cout << "*p = " << *p << "\n";
    
    std::cout << "Pointeur de pointeur\n";
    int ** q = &p;
    **q = 3;
    std::cout << " i = " << i  << "\n";
    std::cout << "*p = " << *p << "\n";
    
    std::cout << "Affectation de nullptr dans p\n";
    p = nullptr;
    std::cout << " i = " << i  << "\n";
    std::cout << " p = " << p  << "\n";
    
    // En décommentant cette ligne, vous aurez une erreur à l'exécution
    //std::cout << "*p = " << *p << "\n";
}
