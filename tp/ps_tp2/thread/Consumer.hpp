/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../ProdOrCons.hpp"
 
#include "osyncstream.hpp"
#include "MessageBox.hpp"


/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons< MessageBox > {
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Consumer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        for (unsigned i = 0; i < nb_messages_; ++i) {
            int message = box_.get();
            if (message < 0) {
                osyncstream{ std::cout } << "Consumer " << name_ << " error: negative message extracted.\n";
            } else {
                osyncstream{ std::cout } << "Consumer " << name_ << " consumed message: " << message << "\n";
            }
            std::this_thread::sleep_for(std::chrono::microseconds{ random_engine_() });
        }
        osyncstream{ std::cout } << "Consumer " << name_ << " finished consuming.\n";
    }
};

