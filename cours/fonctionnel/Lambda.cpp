/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°3
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * Lambda.cpp
 *
 * c++ -std=c++20 Lambda.cpp -o Lambda
 * ./Lambda
 */

#include <iostream>
#include <functional>

int main()
{
    int tab[] = { 1, 2, 3, 4, 5 };
    
    std::cout << "[ ";
    std::for_each( tab, tab + 5, []( int n ) { std::cout << n << " "; });
    std::cout << "]\n";
    
    const int multi = 3;
    int somme = 0;
    auto inc = [multi, &somme]( int & n ) { n *= multi; somme += n; };
    std::for_each( tab, tab + 5, inc );
    
    std::cout << "[ ";
    std::function< void( int ) > display{ []( int n ) { std::cout << n << " "; }};
    std::for_each( tab, tab + 5, display );
    std::cout << "]\nsomme = " << somme << "\n";
}
