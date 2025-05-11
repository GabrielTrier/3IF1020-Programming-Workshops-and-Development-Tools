/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../ProdOrCons.hpp"
 
#include "osyncstream.hpp"
#include "MessageBox.hpp"

/*
 * Producteur de messages
 */
class Producer : public ProdOrCons< MessageBox > {
public:
    // Le constructeur de ProdOrCons peut être utilisé pour Producer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        for (unsigned i = 0; i < nb_messages_; ++i) {
            int message = i;
            box_.put(message);
            osyncstream{ std::cout } << "Producer " << name_ << " producing message: " << message << "\n";
            std::this_thread::sleep_for(std::chrono::microseconds{ random_engine_() });
        }
        osyncstream{ std::cout } << "Producer " << name_ << " finished producing.\n";
    }
};

