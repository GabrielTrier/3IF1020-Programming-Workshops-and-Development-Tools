/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * MessageBox.hpp
 */

#pragma once


#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre processus
 */
using namespace boost::interprocess;
class MessageBox : public BasicMessageBox {
public:
    void put( int message ) {
        scoped_lock<interprocess_mutex> lock(mutex);
        empty.wait(lock, [this]() {return  count_<box_size_ ; });
        basic_put( message );
        count_++;
        full.notify_one();
    }
    int get() {
        scoped_lock<interprocess_mutex> lock(mutex);
        full.wait(lock, [this]() { return count_>0 ; }); 
        int message{ basic_get() };
        count_--;
        empty.notify_one();
        return message;
    }
private:
    interprocess_mutex mutex; 
    interprocess_condition full;
    interprocess_condition empty;
    int count_ = 0 ;
};
 
/*
Voici les outputs du temrinal executant le producer ainsi que celui executant le consumer!
On observe bien qu'il arrivent a communiquer correctement et qu'il y' a une bonne gestion de la mémoire partagée et des synchronisations entre processus.

Producer 1 producing message: 15
Producer 1 producing message: 3
Producer 1 producing message: 48
Producer 1 producing message: 90
Producer 1 producing message: 54
Producer 1 producing message: 55
Producer 1 producing message: 48
Producer 1 producing message: 53
Producer 1 producing message: 82
Producer 1 producing message: 12
Producer 1 producing message: 26
Producer 1 producing message: 85
Producer 1 producing message: 88
Producer 1 producing message: 70
Producer 1 producing message: 73
Producer 1 producing message: 58
Producer 1 producing message: 35
Producer 1 producing message: 75
Producer 1 producing message: 78
Producer 1 producing message: 28
Producer 1 finished producing.

Producer finished.

Consumer 1 consumed message: 15
Consumer 1 consumed message: 3
Consumer 1 consumed message: 48
Consumer 1 consumed message: 90
Consumer 1 consumed message: 54
Consumer 1 consumed message: 55
Consumer 1 consumed message: 48
Consumer 1 consumed message: 53
Consumer 1 consumed message: 82
Consumer 1 consumed message: 12
Consumer 1 consumed message: 26
Consumer 1 consumed message: 85
Consumer 1 consumed message: 88
Consumer 1 consumed message: 70
Consumer 1 consumed message: 73
Consumer 1 consumed message: 58
Consumer 1 consumed message: 35
Consumer 1 consumed message: 75
Consumer 1 consumed message: 78
Consumer 1 consumed message: 28
Consumer 1 finished consuming.
*/