/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système
 * Dominique Marcadet - 2023 - CC BY-SA
 *
 * Thread.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o Thread Thread.cpp
 * Exécution :
 *     ./Thread
 */


#include <iostream>
#include <thread>

using namespace std::chrono_literals;

//#define USE_JTHREAD

struct DoSomething {
    void operator()() {
        std::cout << std::this_thread::get_id() << " will sleep\n";
        std::this_thread::sleep_for( 10ms );
        std::cout << std::this_thread::get_id() << ": bye\n";
    }
};

int main()
{
    DoSomething something;
    std::cout << std::this_thread::get_id() << ": start thread\n";

#ifdef USE_JTHREAD
    std::jthread t{ something };
    std::cout << "thread id is " << t.get_id() << "\n";
#else
    std::thread  t{ something };
    std::cout << "thread id is " << t.get_id() << "\n";
    t.join();
//    t.detach();
#endif

    std::cout << std::this_thread::get_id() << ": done\n";
}

