/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°4
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * Pile_v1.cpp
 *
 * Compilation :
 *     c++ -g -std=c++20 -o Pile_v1 Pile_v1.cpp
 * Exécution :
 *     ./Pile_v1
 *     valgrind ./Pile_v1
 */


#include <iostream>
#include <ios>
#include <stdexcept>

// Définition du type Pile
class  Pile {
public:
        // Déclaration des méthodes
        void     empile( double v );
        double   depile();
        double & sommet();
        // Définition inline de la méthod est_vide()
        bool      est_vide() { return index_ == 0; }

private:
        unsigned int taille_{ 10 };
        double *     tab_   { new double[taille_] };
        unsigned int index_ { 0 };
};

// Définition des méthodes
void Pile::empile( double v )
{
    // objet récepteur : this
    // Pile * const this;
    if( this->index_ < taille_ ) {
        tab_[index_++] = v;
    }
    else {
        throw std::out_of_range( "pile pleine" );
    }
}

double Pile::depile()
{
    if( this->index_ > 0 ) {
        return tab_[--index_];
    }
    throw std::out_of_range( "pile vide" );
}

double & Pile::sommet()
{
    if( this->index_ > 0 ) {
        return tab_[index_ - 1];
    }
    throw std::out_of_range( "pile vide" );
}

int main()
{
    Pile p;

    try {
        std::cout << "p.est_vide() = " << std::boolalpha << p.est_vide() << "\n";
        p.empile( 5 );
        std::cout << "p.est_vide() = " << std::boolalpha << p.est_vide() << "\n";
        std::cout << "p.sommet() = " << p.sommet() << "\n";
        p.sommet() = 8;
        std::cout << "p.depile() = " << p.depile() << "\n";
        std::cout << "p.depile() = " << p.depile() << "\n";
    }
    catch( std::out_of_range e ) {
        std::cout << "erreur : " << e.what() << "\n";
    }
}

