/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Random.hpp
 */

#pragma once

/*******************************************************************

    VOUS N'AVEZ PAS BESOIN DE MODIFIER CE FICHIER

********************************************************************/

#include <random>
 
/*
 * Generateur de nombres aleatoires
 * Il n'est pas necessaire de comprendre son fonctionnement
 *
 * Exemple d'utilisation pour une attente de durée aléatoire entre 0 et 50 ms
 *   Random generator( 50 );
 *   using milliseconds = std::chrono::duration< int, std::milli >;
 *   std::this_thread::sleep_for( milliseconds( generator() ));
 */
class Random {
public:
    explicit Random( int max )
        :  dist_( 0, max )
    {}
 
    int operator()() {
        return dist_( rd_ );
    }
private:
    std::random_device rd_;
    std::uniform_int_distribution< int > dist_;
};

