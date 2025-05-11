/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système
 * Dominique Marcadet - 2023 - CC BY-SA
 *
 * Async.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o Async Async.cpp
 * Exécution :
 *     ./Async
 */


#include <iostream>
#include <thread>
#include <future>

using namespace std::chrono_literals;

int foo() {
    std::cout << "will sleep\n";
    std::this_thread::sleep_for( 10ms );
    std::cout << "bye\n";
    return 42;
}

int main()
{
    std::cout << "start something\n";
    std::future< int > f{ std::async( foo )};
    while( f.wait_for( 1ms ) == std::future_status::timeout ) {
        std::cout << "waiting\n";
    }
    std::cout << "got " << f.get() << "\n";
}

