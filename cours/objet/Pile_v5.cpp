/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°4
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * Pile_v5.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o Pile_v5 Pile_v5.cpp
 * Exécution :
 *     ./Pile_v5
 */


#include <iostream>
#include <ios>
#include <stdexcept>
#include <utility>

#define CONST
//#define CONST const

class  Pile {
public:
        Pile( unsigned int taille = 100 );
        ~Pile();
        Pile( const Pile & p );
        Pile & operator=( const Pile & p );
        void swap( Pile & p );
        
        void     empile( double v );
        double   depile();
        double & sommet() const;
        bool     est_vide() const;

private:
        unsigned int CONST taille_;
        double * CONST tab_;
        unsigned int index_;
};

Pile::Pile( unsigned int taille )
{
    taille_ = taille;
    tab_ = new double[taille_];
    index_ = 0;
    std::cout << "Constructeur\n";
}
/*
Pile::Pile( unsigned int taille )
    : taille_{ taille }
    , tab_{ new double[taille_] }
    , index_{ 0 }
{
    std::cout << "Constructeur\n";
}
*/

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
/*
Pile::Pile( const Pile & p )
    : taille_{ p.taille_ }
    , tab_{ new double[p.taille_] }
    , index_{ p.index_ }
{
    std::cout << "Constructeur de copie\n";
    for( unsigned int i{ 0 }; i < p.index_; ++i ) {
        tab_[i] = p.tab_[i];
    }
}
*/

void Pile::swap( Pile & p )
{
    using std::swap;
    swap( taille_, p.taille_ );
    swap( tab_,    p.tab_ );
    swap( index_,  p.index_ );
}

Pile & Pile::operator=( const Pile & p )
{
    Pile tmp{ p };
    swap( tmp );
    return *this;
}

bool Pile::est_vide() const
{
    //index_ = 7;
    return index_ == 0;
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

int main()
{
    Pile p1{ 10 };
    p1.empile( 5 );
    
    Pile p2( p1 );
    p2 = p1;

    const Pile p3{ 10 };
    // p3.empile( 3 );
    std::cout << "p3.est_vide() = " << std::boolalpha << p3.est_vide() << "\n";
    
    Pile p4[5];
}

