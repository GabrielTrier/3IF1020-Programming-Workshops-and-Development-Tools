/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°6
 * Dominique Marcadet - 2023 - CC BY-SA
 *
 * Ranges.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o Ranges Ranges.cpp
 * Exécution :
 *     ./Ranges
 */


#include <iostream>
#include <iterator>
#include <vector>
#include <ranges>
#include <algorithm>

int main()
{
    using namespace std;
    
    auto const data = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto odd    = []( int i ) { return i % 2 == 1; };
    auto square = []( int i ) { return i * i; };
    
    vector< int > odds;
    copy_if( begin( data ), end( data ), back_inserter( odds ), odd );
    vector< int > squared;
    transform( begin( odds ), end( odds ), back_inserter( squared ), square );
    copy( squared.begin(), squared.end(), ostream_iterator< int >( cout, " " ));
    cout << '\n';
 
    auto r1{ views::filter( data, odd )};
    auto r2{ views::transform( r1, square )};
    copy( r2.begin(), r2.end(), ostream_iterator< int >( cout, " " ));
    cout << '\n';

    // "pipe" syntax
    ranges::copy( data
                    | views::filter( odd )
                    | views::transform( square ),
                  ostream_iterator< int >( cout, " " ));
    cout << '\n';
}
