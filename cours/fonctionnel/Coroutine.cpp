/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°3
 * 
 * Coroutine.cpp
 *
 * Using library https://github.com/andreasbuhr/cppcoro
 *
 * c++ -std=c++20 Coroutine.cpp -o Coroutine -lcppcoro
 * ./Coroutine
 */

#include <iostream>
#include <coroutine>

#include <cppcoro/task.hpp>

cppcoro::task<> counter()
{
    for( unsigned i{ 1 }; ; ++i ) {
        std::cout << "counter: resumed (#" << i << ")\n";
        co_await std::suspend_always{};
    }
}

int main()
{
    auto my_counter{ counter() };
    std::cout << "main: resuming counter\n";
    my_counter.when_ready().m_coroutine.resume();
    std::cout << "main: resuming counter\n";
    my_counter.when_ready().m_coroutine.resume();
}

