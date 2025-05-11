/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * BasicMessageBox.hpp
 */

#pragma once

/*******************************************************************

    VOUS N'AVEZ PAS BESOIN DE MODIFIER CE FICHIER

********************************************************************/

#include <array>
#include <algorithm>

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version sans mécanisme de synchronisation
 */
class BasicMessageBox {
public:
    BasicMessageBox()
        : box_{}
        , put_index_{ 0 }
        , get_index_{ 0 }
    {
        std::fill( box_.begin(), box_.end(), -1 );
    }
    
    void basic_put( int message ) {
        box_[ put_index_ ] = message;
        put_index_ = ( put_index_ + 1 ) % box_size_;
    }
 
    int basic_get() {
        int message{ box_[get_index_] };
        // Pour détecter les erreurs
        box_[get_index_] = -1;
        get_index_ = ( get_index_ + 1 ) % box_size_;
        return message;
    }

protected:
    static const unsigned box_size_ = 2;

private:
    // FIFO réalisée par un tableau géré en tampon circulaire via 2 indices (dépôt et retrait).
    // Les 2 indices sont privés : c'est volontaire, vous ne devez pas les utiliser pour savoir
    // si la boîte est vide ou pleine.
    std::array< int, box_size_ > box_;
    unsigned put_index_;
    unsigned get_index_;
};
 
/*
 * Cette classe est utilisée comme superclasse de thread/MessageBox et process/MessageBox.
 * Pourtant, elle n'a pas de destructeur virtuel, et le polymorphisme n'est pas utilisé
 * pour les 2 méthodes.
 * La raison en est la suivante : dans le cas où producteurs et consommateurs sont des
 * processus, la boîte à lettres est en mémoire partagée, il n'est donc pas possible
 * d'avoir des méthodes virtuelles qui nécessitent l'utilisation d'adresses (celles des
 * méthodes) qui ne peuvent être valides pour tous les processus (espaces mémoires
 * distincts).
 */

