/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système
 * Dominique Marcadet - 2023 - CC BY-SA
 *
 * ProdCons.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o ProdCons ProdCons.cpp
 * Exécution :
 *     ./ProdCons
 */


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>


std::condition_variable cond_place_empty,
                        cond_place_full;
std::mutex data_mutex;
volatile bool data_available{ false };
volatile int data{ 0 };

bool done() { return false; }

void create_data()
{
    std::cout << "create data\n";
}

void get_data_from_place()
{
    std::cout << "get data : " << data << "\n";
    data = 0;
}

void put_data_into_place()
{
    static int d{ 1 };
    std::cout << "put data : " << d << "\n";
    data = d++;
}

void process_data()
{
    std::cout << "process data\n";
}

struct producer { 
  void operator()() {
    while( !done() ) { 
      create_data(); 
      {
        std::unique_lock lock{ data_mutex };
        if( data_available ) { 
          cond_place_empty.wait( lock );
        }
        put_data_into_place(); 
        data_available = true; 
        cond_place_full.notify_one();
      }
    } 
  } 
};

struct consumer { 
  void operator()() {
    while( !done() ) { 
      {
        std::unique_lock lock{ data_mutex };
        if( ! data_available ) { 
          cond_place_full.wait( lock );
        }
        get_data_from_place(); 
        data_available = false; 
        cond_place_empty.notify_one();
      }
      process_data(); 
    } 
  } 
};


int main() {
  std::thread c{ consumer{} }, p{ producer{} };

  c.join();
  p.join();
}


