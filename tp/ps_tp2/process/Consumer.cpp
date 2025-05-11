/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.cpp
 * c++ -std=c++20 Consumer.cpp -o Consumer -lpthread -lrt
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
 * Consommateur de messages
 */
class Consumer : public ProdOrCons<MessageBox> {
public:
    using ProdOrCons::ProdOrCons;

    void operator()() override {
        Random random_wait(50); // Temps d'attente entre les retraits
        for (int i = 0; i < nb_messages_; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(random_wait() * 10));
            int message = box_.get();
            if (message >= 0) {
                std::cout << "Consumer " << name_ << " consumed message: " << message << "\n";
            } else {
                std::cerr << "Consumer " << name_ << " error: negative message extracted.\n";
            }
        }
        std::cout << "Consumer " << name_ << " finished consuming.\n";
    }
};

int main() {
    using namespace boost::interprocess;
    bool semaphore_ready = false; // Bool du statut de la boite
    while (!semaphore_ready) {
        try {
            named_semaphore semaphore(open_or_create, "semaphore_shared_memory_ready", 0);
            semaphore.wait(); // Attente du signal du producer
            semaphore_ready = true; // Statut change!
            
            // Ouvre l'objet de mémoire partagée en mode lecture-écriture
            shared_memory_object shm_obj(open_only, "shared_memory", read_write);
            mapped_region region(shm_obj, read_write);
            MessageBox* box = static_cast<MessageBox*>(region.get_address());

            if (!box) {
                std::cerr << "Error: message box not found." << std::endl;
                return 1;
            }

            Random generator(50);
            Consumer consumer(1, *box, generator, 20); //Consommateur doit lire les 20 messages (même nbr de message que produceur)
            consumer();
        } catch (const interprocess_exception& ex) {
            std::cerr << "Interprocess synchronization error: " << ex.what() << std::endl;
        }
    }
    return 0;
}