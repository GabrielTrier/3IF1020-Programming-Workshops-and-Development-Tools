/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Threads.cpp
 * c++ -std=c++20 Threads.cpp -o Threads -lpthread
 */

#include <iostream>
#include <thread>
#include "../Random.hpp"
#include "osyncstream.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"
#include "MessageBox.hpp"
 
/*
 * Test avec 1 producteur et 1 consommateur
 */
void one_producer_one_consumer() {
    MessageBox box;
    Random random_engine(50);
    Producer producer(1, box, random_engine, 20);
    Consumer consumer(1, box, random_engine, 20);

    std::thread producer_thread(std::ref(producer));
    std::thread consumer_thread(std::ref(consumer));

    producer_thread.join();
    consumer_thread.join();
}

/*
 * Test avec plusieurs producteurs et consommateurs
 */
void several_producers_and_consumers() {
    Random random_engine(50);
    MessageBox box;

    // Generate a random number of consumers between 10 and 20
    int nb_consumers = random_engine() % 11 + 10;
    std::cout << "Number of consumers: " << nb_consumers << std::endl;

    // Set the number of producers to twice the number of consumers
    int nb_producers = nb_consumers * 2;
    std::cout << "Number of producers: " << nb_producers << std::endl;

    std::vector<std::thread> group;

    // Create consumer threads
    for (int i = 0; i < nb_consumers; ++i) {
        group.push_back(std::thread{Consumer(i, box, random_engine, 20)});
    }

    // Create producer threads
    for (int i = 0; i < nb_producers; ++i) {
        group.push_back(std::thread{Producer(i, box, random_engine, 10)});
    }

    // Wait for all threads to finish execution
    for (auto &thread : group) {
        thread.join();
    }
}

int main() {
    //one_producer_one_consumer();
    several_producers_and_consumers();
    return 0;
}
