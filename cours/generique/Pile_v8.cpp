/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°5
 * Dominique Marcadet - 2023 - CC BY-SA
 *
 * Pile_v8.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o Pile_v8 Pile_v8.cpp
 * Exécution :
 *     ./Pile_v8
 */

#include <iostream>
#include <ios>
#include <stdexcept>
#include <utility>
#include <string>


template< typename T, unsigned TAILLE >
class  Pile {
public:

    Pile() = default;

    template< unsigned SIZE >
    Pile( const Pile< T, SIZE > & p );
    
    template< typename U, unsigned SIZE >
    Pile & operator=( const Pile< U, SIZE > & p );

    void empile( const T & v );
    T    depile();
    T &  sommet();
    bool est_vide() const { return index_ == 0; }

private:
    T tab_[TAILLE];
    unsigned index_ = 0;

    template< typename U, unsigned SIZE >
    friend class Pile;
};

template< typename T, unsigned TAILLE >
template< unsigned SIZE >
Pile< T, TAILLE >::Pile( const Pile< T, SIZE > & p )
    : index_{ std::min( p.index_, TAILLE )}
{
    for( unsigned i{ 0 }; i < index_; ++i ) {
        tab_[i] = p.tab_[i];
    }
}

template< typename T, unsigned TAILLE >
template< typename U, unsigned SIZE >
Pile< T, TAILLE > & Pile< T, TAILLE >::operator=( const Pile< U, SIZE > & p )
{
    index_ = std::min( p.index_, TAILLE );
    for( unsigned i{ 0 }; i < index_; ++i ) {
        tab_[i] = p.tab_[i];
    }
    return *this;
}

template< typename T, unsigned TAILLE >
void Pile< T, TAILLE >::empile( const T & v )
{
    if( this->index_ < TAILLE ) {
        tab_[index_++] = v;
    }
    else {
        throw std::out_of_range( "pile pleine" );
    }
}

template< typename T, unsigned TAILLE >
T & Pile< T, TAILLE >::sommet()
{
    if( this->index_ > 0 ) {
        return tab_[index_ - 1];
    }
    throw std::out_of_range( "pile vide" );
}

template< typename T, unsigned TAILLE >
T Pile< T, TAILLE >::depile()
{
    if( this->index_ > 0 ) {
        return tab_[--index_];
    }
    throw std::out_of_range( "pile vide" );
}

int main()
{
    Pile< double, 10 > p1;
    
    Pile< double, 11 > p2{ p1 };

    Pile< int, 10 > p3;
    p1 = p3;

    Pile< std::string, 10 > p4;
    //p1 = p4;
}

