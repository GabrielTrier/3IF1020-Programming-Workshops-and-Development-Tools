/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°1
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * InputOutput.c
 *
 * Compilation avec édition de liens :
 *     c++ -std=c++20 -o InputOutput InputOutput.cpp
 *
 * Exécution :
 *     ./InputOutput
 */

// Fichier d'entête de la bibliothèque standard d'entrées/sorties C++
#include <iostream>

int main() {
    // std::cout représente la sortie standard
    std::cout << "Donner un nombre : ";
    int n{};
    // std::cin représente l'entrée standard
    std::cin >> n;
    if( std::cin.good() ) {
        std::cout << "Le carré de " << n << " est " << n * n << "\n";
    }
    return 0;
}
