/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°4
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * Pile_v4.cpp
 *
 * Compilation :
 *     c++ -g -std=c++20 -o Pile_v4 Pile_v4.cpp
 * Exécution :
 *     ./Pile_v4
 *     valgrind ./Pile_v4
 */

//#define DEFINE_COPY_ASSIGNMENT

#include <iostream>
#include <ios>
#include <stdexcept>
#include <utility>

class  Pile {
public:
        Pile( unsigned int taille );
        ~Pile();
        Pile( const Pile & p );

#ifdef DEFINE_COPY_ASSIGNMENT
        // Affectation par copie
        Pile & operator=( const Pile & p );
        void swap( Pile & p );
#endif
        
        void     empile( double v );
        double   depile();
        double & sommet();
        bool     est_vide() { return index_ == 0; }

private:
        unsigned int taille_;
        double * tab_;
        unsigned int index_;
};

Pile::Pile( unsigned int taille )
{
    std::cout << "Constructeur : " << taille << "\n";
    taille_ = taille;
    tab_ = new double[taille_];
    index_ = 0;
}

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

#ifdef DEFINE_COPY_ASSIGNMENT
void Pile::swap( Pile & p )
{
    using std::swap;
    swap( taille_, p.taille_ );
    swap( tab_,    p.tab_ );
    swap( index_,  p.index_ );
}

Pile & Pile::operator=( const Pile & p )
{
    std::cout << "Affectation par copie\n";
    Pile tmp{ p };
    swap( tmp );
    return *this;
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

int main()
{
    Pile p1{ 10 };
    p1.empile( 5 );
    Pile p2{ 20 };
    p2 = p1;
}

