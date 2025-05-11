/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°6
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * Move.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o Move Move.cpp
 * Exécution :
 *     ./Move
 */


#include <iostream>
#include <utility>

struct A {
    A() { std::cout << "default constructor\n"; }
    ~A() { std::cout << "destructor\n"; }

    A( const A & ) { std::cout << "copy constructor\n"; }
    A & operator=( const A & ) { std::cout << "copy assignment\n"; return *this; }

//     A( A && ) { std::cout << "move constructor\n"; }
//     A & operator=( A && ) { std::cout << "move assignment\n"; return *this; }
};

int main()
{
    A a1;
    A a2;
    std::swap( a1, a2 );
}

