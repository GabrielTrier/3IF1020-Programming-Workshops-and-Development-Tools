/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°5
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * Pile_v6.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o Pile_v6 Pile_v6.cpp
 * Exécution :
 *     ./Pile_v6
 */

#include <iostream>
#include <ios>
#include <stdexcept>
#include <utility>
#include <string>

template< typename T >
class  Pile {
public:
        Pile( unsigned int taille = 100 );
        ~Pile();
        Pile( const Pile< T > & p );

        Pile & operator=( const Pile< T > & p );
        void swap( Pile & p );
        
        void empile( const T & v );
        T    depile();
        T &  sommet();
        bool est_vide() const { return index_ == 0; }

private:
        unsigned int taille_;
        T * tab_;
        unsigned int index_;
};

template< typename T >
Pile< T >::Pile( unsigned int taille )
{
    taille_ = taille;
    tab_ = new T[taille_];
    index_ = 0;
}

template< typename T >
Pile< T >::Pile( const Pile< T > & p )
{
    taille_ = p.taille_;
    index_ = p.index_;
    tab_ = new T[taille_];
    for( unsigned int i{ 0 }; i < p.index_; ++i ) {
        tab_[i] = p.tab_[i];
    }
}

template< typename T >
void Pile< T >::swap( Pile< T > & p )
{
    using std::swap;
    swap( taille_, p.taille_ );
    swap( tab_,    p.tab_ );
    swap( index_,  p.index_ );
}

template< typename T >
Pile< T > & Pile< T >::operator=( const Pile< T > & p )
{
    Pile< T > tmp{ p };
    swap( tmp );
    return *this;
}

template< typename T >
Pile< T >::~Pile()
{
    delete[] tab_;
}

template< typename T >
void Pile< T >::empile( const T & v )
{
    if( this->index_ < taille_ ) {
        tab_[index_++] = v;
    }
    else {
        throw std::out_of_range( "pile pleine" );
    }
}

template< typename T >
T & Pile< T >::sommet()
{
    if( this->index_ > 0 ) {
        return tab_[index_ - 1];
    }
    throw std::out_of_range( "pile vide" );
}

template< typename T >
T Pile< T >::depile()
{
    if( this->index_ > 0 ) {
        return tab_[--index_];
    }
    throw std::out_of_range( "pile vide" );
}

int main()
{
    Pile< double > p1{ 10 };
    p1.empile( 5 );
    
    Pile< int > p2{ 10 };
    //p2 = p1;
    
    Pile< Pile< double >> p3;
    p3.empile( p1 );
    p3.sommet().empile( 1 );
    std::cout << "p1.sommet() = " << p1.sommet() << "\n";
    std::cout << "p3.sommet().sommet() = " << p3.sommet().sommet() << "\n";
}

