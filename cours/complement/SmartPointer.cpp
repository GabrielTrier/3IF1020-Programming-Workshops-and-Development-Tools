/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°6
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * SmartPointer.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o SmartPointer SmartPointer.cpp
 * Exécution :
 *     ./SmartPointer
 */


#include <iostream>
#include <utility>
#include <memory>

struct A {
    A( int a ) : a_{ a } { std::cout << "constructor with " << a_ << "\n"; }
    ~A() { std::cout << "destructor for " << a_ << "\n"; }

     A( A && ) { std::cout << "move constructor\n"; }
     A & operator=( A && ) { std::cout << "move assignment\n"; return *this; }
 
    int a_;
};

int main()
{
    std::shared_ptr< A > s1{ new A{ 1 } };
    std::cout << s1->a_ << "\n";
    
    auto s2{ std::make_shared< A >( 2 )};
    std::cout << (*s2).a_ << "\n";
    
    std::cout << "count1 = " << s2.use_count() << "\n";
    {
        auto s3{ s2 };
        std::cout << s3->a_ << "\n";
        std::cout << "count2 = " << s2.use_count() << "\n";
    }
    std::cout << "count3 = " << s2.use_count() << "\n";
    
    auto u1{ std::make_unique< A >( 3 )};
    // auto u2{ u1 };
    auto u2{ std::move( u1 )};
}

