/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°6
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * Sac.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o Sac Sac.cpp
 * Exécution :
 *     ./Sac
 */


#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <iterator>

struct Fruit { std::string nom_; };
struct Pomme : Fruit {};

int main()
{
    std::vector< Fruit > sf{ Fruit{ "f1" } };
    std::vector< Pomme > sp{ Pomme{ "p1" } };
    //sf = sp;

    auto print = []( const Fruit * f ) { std::cout << f->nom_ << " "; };

    std::vector< Fruit * > spf{ new Fruit{ "f1" }, new Pomme{ "p1" }};
    std::ranges::for_each( spf, print );
    std::cout << '\n';
    
    std::vector< Pomme * > spp{ new Pomme{ "p2" }, new Pomme{ "p3" }};
    std::ranges::for_each( spp, print );
    std::cout << '\n';
    //spf = spp;
    std::copy( spp.begin(), spp.end(), std::back_inserter( spf ));
    std::ranges::for_each( spf, print );
    std::cout << '\n';

    std::shared_ptr< Fruit > pf{ new Fruit{} };
    std::shared_ptr< Pomme > pp( new Pomme{} );
    pf = pp;
}
