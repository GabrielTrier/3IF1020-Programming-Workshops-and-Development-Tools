/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * MessageBox.hpp
 */

#pragma once

#include <mutex>
#include <condition_variable>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'échange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre threads
 */
class MessageBox : public BasicMessageBox {
public:
    void put(int message) {
        std::unique_lock<std::mutex> lock(mutex_);
        // Attendre tant que la boîte est pleine
        cond_not_full_.wait(lock, [this] { return count_ < box_size_; });
        basic_put( message );   
        ++count_;
        cond_not_empty_.notify_one();// Notifier un consommateur qu'un message est disponible
    }

    int get() {
        std::unique_lock<std::mutex> lock(mutex_);
        // Attendre tant que la boîte est vide
        cond_not_empty_.wait(lock, [this] { return count_ > 0; });
        int message = basic_get();  
        --count_; 
        cond_not_full_.notify_one();// Notifier un producteur qu'une place est disponible
        return message;
    }
private:
    std::mutex mutex_;// Mutex pour protéger l'accès à la boîte
    std::condition_variable cond_not_full_;// Condition pour les producteurs (boîte non pleine)
    std::condition_variable cond_not_empty_;// Condition pour les consommateurs (boîte non vide)
    int count_ = 0;// Compteur du nombre de messages dans la boîte
};

/* On remarque bien que nous avons plus l'erreur d’extraction de messages négatifs ( Consumer 1 error: negative message extracted.)
Cela indique bien que la synchronisation empêche le consommateur d’accéder à la boîte lorsqu’elle est vide!

Output: 
Producer 1 producing message: 0
Producer 1 producing message: 1
Consumer 1 consumed message: 0
Consumer 1 consumed message: 1
Producer 1 producing message: 2
Consumer 1 consumed message: 2
Producer 1 producing message: 3
Consumer 1 consumed message: 3
Producer 1 producing message: 4
Consumer 1 consumed message: 4
Producer 1 producing message: 5
Consumer 1 consumed message: 5
Producer 1 producing message: 6
Consumer 1 consumed message: 6
Producer 1 producing message: 7
Consumer 1 consumed message: 7
Producer 1 producing message: 8
Consumer 1 consumed message: 8
Producer 1 producing message: 9
Consumer 1 consumed message: 9
Producer 1 producing message: 10
Consumer 1 consumed message: 10
Producer 1 producing message: 11
Producer 1 producing message: 12
Consumer 1 consumed message: 11
Producer 1 producing message: 13
Consumer 1 consumed message: 12
Producer 1 producing message: 14
Consumer 1 consumed message: 13
Consumer 1 consumed message: 14
Producer 1 producing message: 15
Consumer 1 consumed message: 15
Producer 1 producing message: 16
Consumer 1 consumed message: 16
Producer 1 producing message: 17
Consumer 1 consumed message: 17
Producer 1 producing message: 18
Consumer 1 consumed message: 18
Producer 1 producing message: 19
Producer 1 finished producing.
Consumer 1 consumed message: 19
Consumer 1 finished consuming.
*/
