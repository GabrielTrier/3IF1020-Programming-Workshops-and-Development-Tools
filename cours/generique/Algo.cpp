
/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°5
 * Dominique Marcadet - 2023 - CC BY-SA
 *
 * Algo.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o Algo Algo.cpp
 * Exécution :
 *     ./Algo
 */

#include <iostream>
#include <list>
#include <vector>

void foo1() {
  int tab[10];

  for( int i = 0; i < 10; ++i ) {
    tab[i] = 1;
  }

  std::cout << "foo1  : ";
  for( int i = 0; i < 10; ++i ) std::cout << tab[i] << " ";
  std::cout << "\n";
}

void foo2() {
  int tab[10];

  for( int * p = tab; p != tab + 10; ++p ) {
    *p = 1;
  }

  std::cout << "foo2  : ";
  for( int i = 0; i < 10; ++i ) std::cout << tab[i] << " ";
  std::cout << "\n";
}

void foo3()
{
  std::vector< int > tab( 10 );

  for( std::vector< int >::iterator
              p{   tab.begin() };
              p != tab.end();
            ++p ) {
    *p = 1;
  }

  std::cout << "foo3  : ";
  for( int i = 0; i < 10; ++i ) std::cout << tab[i] << " ";
  std::cout << "\n";
}

void foo4()
{
  std::vector< int > tab( 10 );

  for( auto p{   std::begin( tab )};
            p != std::end  ( tab );
          ++p ) {
    *p = 1;
  }

  std::cout << "foo4  : ";
  for( int i = 0; i < 10; ++i ) std::cout << tab[i] << " ";
  std::cout << "\n";
}

void foo5()
{
  std::vector< int > tab( 10 );
  //std::list< int > tab{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  for( auto & p : tab ) {
    p = 1;
  }

  std::cout << "foo5  : ";
  for( auto p : tab ) std::cout << p << " ";
  std::cout << "\n";
}

template< typename Container >
void mettre_a_1( Container & c )
{
  for( auto & p : c ) p = 1;
}

void foo6()
{
  std::vector< int > tab( 10 );

  mettre_a_1( tab );

  std::cout << "foo6  : ";
  for( auto p : tab ) std::cout << p << " ";
  std::cout << "\n";
}

template< typename Iter >
void mettre_a_1( Iter begin, Iter end )
{
  for( Iter p{ begin }; p != end; ++p ) {
    *p = 1;
  }
}

void foo7()
{
  std::vector< int > tab( 10 );

  mettre_a_1( std::begin( tab ),
              std::end  ( tab ));

  std::cout << "foo7  : ";
  for( auto p : tab ) std::cout << p << " ";
  std::cout << "\n";
}

template< typename Iter, typename T >
void mettre_a_val( Iter beg, Iter end, T val )
{
  for( Iter p{ beg }; p != end; ++p ) {
    *p = val;
  }
}

void foo8()
{
  std::vector< int > tab( 10 );

  mettre_a_val( std::begin( tab ),
                std::end  ( tab ), 1 );

  std::cout << "foo8  : ";
  for( auto p : tab ) std::cout << p << " ";
  std::cout << "\n";
}

template< typename Iter, typename F >
void apply( Iter beg, Iter end, const F & fun )
{
  for( Iter p{ beg }; p != end; ++p ) fun( *p );
}

void mettre_a_1_bis( int & v ) { v = 1; }

void foo9()
{
  std::vector< int > tab( 10 );

  apply( std::begin( tab ),
         std::end  ( tab ), &mettre_a_1_bis );

  std::cout << "foo9  : ";
  for( auto p : tab ) std::cout << p << " ";
  std::cout << "\n";
}

template< typename T >
struct mettre_a_val_bis {
  mettre_a_val_bis( T val ) : val_{ val } {}

  void operator()( T & t ) const { t = val_; }
  const T val_;
};

void foo10()
{
  std::vector< int > tab( 10 );

  apply( std::begin( tab ),
         std::end  ( tab ), mettre_a_val_bis( 1 ));

  std::cout << "foo10 : ";
  for( auto p : tab ) std::cout << p << " ";
  std::cout << "\n";
}

int main()
{
    foo1();
    foo2();
    foo3();
    foo4();
    foo5();
    foo6();
    foo7();
    foo8();
    foo9();
    foo10();
}

