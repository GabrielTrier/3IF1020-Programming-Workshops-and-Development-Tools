/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°4
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * Pile_v3.cpp
 *
 * Compilation :
 *     c++ -g -std=c++20 -o Pile_v3 Pile_v3.cpp
 * Exécution :
 *     ./Pile_v3
 *     valgrind ./Pile_v3
 */

//#define DEFINE_COPY_CONSTRUCTOR

#include <iostream>
#include <ios>
#include <stdexcept>

class  Pile {
public:
        Pile( unsigned int taille );
        ~Pile();

#ifdef DEFINE_COPY_CONSTRUCTOR
        // Constructeur de copie
        Pile( const Pile & p );
#endif
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

#ifdef DEFINE_COPY_CONSTRUCTOR
Pile::Pile( const Pile & p )
{
    std::cout << "Constructeur de copie\n";
    taille_ = p.taille_;
    index_ = p.index_;
    tab_ = new double[taille_];
    for( unsigned int i{ 0 }; i < p.index_; ++i ) {
        tab_[i] = p.tab_[i];
    }
}
#endif

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

double & Pile::sommet()
{
    if( this->index_ > 0 ) {
        return tab_[index_ - 1];
    }
    throw std::out_of_range( "pile vide" );
}

void f( Pile p )
{
    std::cout << "f()\n";
}

int main()
{
    Pile p1{ 10 };
    Pile p2{ p1 };
    p1.empile( 12 );
    p2.empile( 5 );

    std::cout << "p1.sommet() = " << p1.sommet() << "\n";
    std::cout << "p2.sommet() = " << p2.sommet() << "\n";
    
    //f( p1 );
}

