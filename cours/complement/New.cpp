/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°6
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * New.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o New New.cpp
 * Exécution :
 *     ./New
 */

#include <iostream>
#include <vector>
#include <new>

struct A {
    int a_;
    A( int a ) : a_{ a } { std::cout << "A constructor\n"; }
    ~A() { std::cout << "A destructor\n"; }
    void * operator new( size_t s );
    void   operator delete( void * p );
};

size_t allocator_index{ 0 };
char bufA[3 * sizeof( A )];

void * A::operator new( size_t s ) {
    std::cout << "A::operator new\n";
    return bufA + allocator_index++ * sizeof( A );
}

void A::operator delete( void * p ) {
    std::cout << "A::operator delete\n";
}

struct B {
    int b_;
    B( int b ) : b_{ b } { std::cout << "B constructor\n"; }
    ~B() { std::cout << "B destructor\n"; }
};
char bufB[sizeof( B )];


int main()
{
    std::vector< A * > v;
    for( int i{ 0 }; i < 3; ++i ) {
        v.push_back( new A{ i });
    }
    for( int i{ 0 }; i < 3; ++i ) {
        delete v[i];
    }
    
    B * b = new( bufB ) B{ 42 };
    //delete b;
    //b->~B();
}

