/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.cpp
 * c++ -std=c++20 Producer.cpp -o Producer -lpthread -lrt
 */

#include <iostream>
#include <thread>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>

#include "../Random.hpp"
#include "../ProdOrCons.hpp"
#include "MessageBox.hpp"

/*
 * Producteur de messages
 */
class Producer : public ProdOrCons<MessageBox> {
public:
    using ProdOrCons::ProdOrCons;

    void operator()() override {
        Random random_wait(1000); // Temps d'attente entre les dépôts
        for (int i = 0; i < nb_messages_; ++i) {
            int message = random_wait() % 100; 
            box_.put(message);
            std::cout << "Producer " << name_ << " producing message: " << message << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(random_wait()));
        }
        std::cout << "Producer " << name_ << " finished producing.\n" << std::endl;
    }
};

int main() {
    using namespace boost::interprocess;

    // Initialisation de la mémoire partagée et de la sémaphore pour la synchronisation
    shared_memory_object::remove("shared_memory");
    shared_memory_object shm_obj(create_only, "shared_memory", read_write);
    shm_obj.truncate(sizeof(MessageBox)); // Définissions de la taille 
    mapped_region region(shm_obj, read_write);
    MessageBox* box = new (region.get_address()) MessageBox(); //Initialisisation de la boîte à l'adresse de la région mappée

    // Initialisation et signalement avec un sémaphore nommé
    named_semaphore::remove("semaphore_shared_memory_ready");
    named_semaphore semaphore(open_or_create, "semaphore_shared_memory_ready", 0);

    // Signalement du bon statut de la mémoire partagée 
    semaphore.post();

    Random generator(50);
    Producer producer(1, *box, generator, 20); // 20 Messages à produire ici
    producer();

    // Nettoyage en supprimant les sémaphores
    named_semaphore::remove("semaphore_shared_memory_ready");
    std::cout << "Producer finished." << std::endl;

    return 0;
}