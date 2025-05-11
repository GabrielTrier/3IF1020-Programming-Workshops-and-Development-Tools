/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°3
 * Fibonacci.cpp
 *
 * Using library https://github.com/andreasbuhr/cppcoro
 * Example from this library
 *
 * c++ -std=c++20 Fibonacci.cpp -o Fibonacci
 * ./Fibonacci
 */


#include <iostream>
#include <cstdint>

#include <cppcoro/generator.hpp>


cppcoro::generator< std::uint64_t > fibonacci()
{
  std::uint64_t a = 0, b = 1;
  while( true ) {
    co_yield b;
    auto tmp = a;
    a = b;
    b += tmp;
  }
}

int main()
{
  for( auto i : fibonacci() ) {
    if( i > 1'000'000 ) break;
    std::cout << i << std::endl;
  }
}

