/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°4
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * Pile_v2.cpp
 *
 * Compilation :
 *     c++ -g -std=c++20 -o Pile_v2 Pile_v2.cpp
 * Exécution :
 *     ./Pile_v2
 *     valgrind ./Pile_v2
 */


#include <iostream>
#include <ios>
#include <stdexcept>

class  Pile {
public:
        // Constructeur et destructeur
        Pile( unsigned int taille );
        ~Pile();
        
        void     empile( double v );
        double   depile();
        double & sommet();
        bool     est_vide() { return index_ == 0; }

private:
        unsigned int taille_;
        double *     tab_;
        unsigned int index_;
};

Pile::Pile( unsigned int taille )
{
    std::cout << "Constructeur : " << taille << "\n";
    taille_ = taille;
    tab_ = new double[taille_];
    index_ = 0;
}

Pile::~Pile()
{
    std::cout << "Destructeur\n";
    delete[] tab_;
}

void Pile::empile( double v )
{
    if( this->index_ < taille_ ) {
        tab_[index_++] = v;
    }
    else {
        throw std::out_of_range( "pile pleine" );
    }
}

Pile pg{ 5 };

int main()
{
    //Pile p;
    Pile p{ 10 };

    std::cout << "p.est_vide() = " << std::boolalpha << p.est_vide() << "\n";
    p.empile( 5 );
    std::cout << "p.est_vide() = " << std::boolalpha << p.est_vide() << "\n";
}
