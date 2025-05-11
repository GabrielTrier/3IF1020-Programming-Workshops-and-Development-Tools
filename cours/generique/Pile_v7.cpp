/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°5
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * Pile_v7.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o Pile_v7 Pile_v7.cpp
 * Exécution :
 *     ./Pile_v7
 */

#include <iostream>
#include <ios>
#include <stdexcept>
#include <utility>
#include <string>

template< typename T, unsigned TAILLE >
class  Pile {
public:
        void empile( const T & v );
        T    depile();
        T &  sommet();
        bool est_vide() const { return index_ == 0; }

private:
        T tab_[TAILLE];
        unsigned int index_ = 0;
};

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
    p1.empile( 5 );
    
    //Pile< double, 11 > p2{ p1 };

    Pile< int, 10 > p3;
    //p1 = p3;
    
    Pile< double, 10 > p4;
    p4 = p1;
    
    Pile< Pile< double, 10 >, 10 > p5;
    p5.empile( p1 );
    p5.sommet().empile( 1 );
    std::cout << "p1.sommet() = " << p1.sommet() << "\n";
    std::cout << "p3.sommet().sommet() = " << p5.sommet().sommet() << "\n";
}

