/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°2
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * Allocation.cpp
 *
 * Compilation :
 *      c++ -g -std=c++20 Allocation.cpp -o Allocation
 * Exécution :
 *      ulimit -v 10000000
 *      ./Allocation
 *      valgrind ./Allocation
 */

#include <iostream>

// Variable globale : accessible par toutes les fonctions
// Variable allouée statiquement avant la première instruction de main()
int globale{ 7 };

void foo()
{
    // Variables locales : accessibles uniquement dans foo()
    // Variable locale allouée automatiquement
    int automatique{ 5 };
    // Variable locale allouée dynamiquement
    int * dynamique{ new int{ 33 } };
    // Variable locale allouée statiquement
    static int statique{ 587 };

    ++globale; ++automatique; ++*dynamique; ++statique;
    
    // automatique et *dynamique sont recréés à chaque appel de foo()
    std::cout << "automatique = " << automatique << "\n";
    std::cout << "*dynamique = " << *dynamique << "\n";
    // statique conserve sa valeur d'un appel de foo() à l'autre
    std::cout << "statique = " << statique << "\n";
    
    // Sans cette instruction, fuite de mémoire
    // Commenter cette ligne et lancer l'exécutable via valgrind
    delete dynamique;
    // Destruction de automatique après la sortie de foo()
}

void bar()
{
    static unsigned nb = 0;
    while( true ) {
        std::cout << "nb = " << ++nb << "\n";
        // Les apostrophes, qui facilitent la lecture du nombre, sont ignorés
        new int[1'000'000];
    }
}

int main()
{
    std::cout << "globale = " << globale << "\n";
    std::cout << "Premier appel de foo()\n";
    foo();
    std::cout << "Second appel de foo()\n";
    foo();
    // globale aura été incrémentée 2 fois
    std::cout << "globale = " << globale << "\n";
    
    // La commande ulimit a limité la taille maximale du tas
    // En décommentant l'appel à bar(), il y aura une erreur à l'exécution quand le tas sera épuisé
    // Le lancement de l'exécutable via valgrind montre la fuite de mémoire
    //bar();
}

// Destruction de globale après la sortie de main()
// Destruction de statique après la sortie de main()
