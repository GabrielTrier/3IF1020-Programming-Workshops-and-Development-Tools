/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°2
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * Struct.cpp
 *
 * Compilation :
 *      c++ -std=c++20 Struct.cpp -o Struct
 * Exécution :
 *      ./Struct
 */

#include <iostream>
#include <string>

enum class Sexe { Homme, Femme };
// Énumération issue de C :
// enum Sexe { Homme, Femme };

// Le caractère _ à la fin du nom de l'attribut est une convention
// que j'utilise, il n'est pas obligatoire
struct Personne {
    std::string nom_;
    Sexe sexe_;
    int age_;
};

int main()
{
    Personne p1;
    // En C :
    // struct Personne p1;
    // Sauf si on dit que Personne est la même chose que struct Personne avec
    // typedef struct Personne Personne;
    p1.nom_ = "Paul";
    p1.sexe_ = Sexe::Homme;
    // Avec l'énumération C :
    //p1.sexe_ = Homme;
    p1.age_ = 23;
    std::cout << p1.nom_ << " a " << p1.age_ << " ans\n";
    
    // Allocation dynamique possible
    Personne * p2 = new Personne{ "Anne", Sexe::Femme, 34 };
    // L'opérateur -> permet d'éviter les parenthèses
    std::cout << (*p2).nom_ << " a " << p2->age_ << " ans\n";
    delete p2;
}
