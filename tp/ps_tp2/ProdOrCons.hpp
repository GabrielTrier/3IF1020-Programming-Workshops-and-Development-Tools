/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * ProdOrCons.hpp
 */

#pragma once

/*******************************************************************

    VOUS N'AVEZ PAS BESOIN DE MODIFIER CE FICHIER

********************************************************************/

#include "Random.hpp"


// Le type de la boîte à lettres est un paramètre de généricité
template< typename MB >
class ProdOrCons {
public:
    ProdOrCons( unsigned name, MB & box, Random & engine, unsigned nb_messages )
        : name_(name)
        , box_( box )
        , random_engine_( engine )
        , nb_messages_( nb_messages )
    {}
 
    virtual ~ProdOrCons() {}
 
    virtual void operator()() = 0;
 
protected:
    // nom sous la forme d'un entier
    const unsigned name_;
    // FIFO où écrire/lire les messages
    MB & box_;
    // générateur de nombres aléatoires
    Random & random_engine_;
    // nombre de messages à produire ou lire
    const unsigned nb_messages_;
};
 
