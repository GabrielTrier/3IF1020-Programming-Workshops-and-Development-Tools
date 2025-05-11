/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°1
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * CallHello.cpp
 *
 * Compilation avec édition de liens :
 *     c++ -o CallHello CallHello.cpp Hello.cpp
 * Exécution :
 *     ./CallHello
 *
 * Compilation séparée puis édition de liens :
 *     c++ -c CallHello.cpp
 *     c++ -c Hello.cpp
 *     c++ -o CallHello CallHello.o Hello.o
 * Exécution :
 *     ./CallHello
 */

// Inclusion du fichier d'entête
#include "Hello.hpp"

// Les arguments de la ligne de commande ne sont pas utilisés, il est inutile de préciser
// les paramètres de main()
int main()
{
    hello();
    return 0;
}
