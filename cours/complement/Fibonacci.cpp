/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°6
 * Dominique Marcadet - 2023 - CC BY-SA
 *
 * Fibonacci.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o Fibonacci Fibonacci.cpp
 * Exécution :
 *     ./Fibonacci
 */



#include <iostream>
#include <ranges>
#include <random>

class Fibonacci : public std::ranges::view_interface< Fibonacci > {

    using value_type = std::uint64_t;
    
    class iterator {
        value_type previous_;
        value_type current_;
    public:
        iterator() : previous_( 0 ), current_( 1 ) {}

        value_type operator*() const {
            return current_;
        }

        bool operator!=( const iterator & ) const {
            return true;
        }

        iterator & operator++() {
            value_type next = previous_ + current_;
            previous_ = current_;
            current_ = next;
            return *this;
        }
    };

public:
    iterator begin() {
        return iterator{};
    }

    iterator end() {
        return iterator{};
    }
};

int main()
{
    Fibonacci fibonacci;
    for( auto i : fibonacci ) {
        if( i > 1'000'000 ) break;
        std::cout << i << std::endl;
    }
}
