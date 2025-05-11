/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°2
 * Dominique Marcadet - 2022-23 - CC BY-SA
 *
 * Reference.cpp
 *
 * Compilation :
 *      c++ -std=c++20 Reference.cpp -o Reference
 * Exécution :
 *      ./Reference
 */

#include <iostream>

int main()
{
    int    i{ 3 };
    // ri est une référence sur la valeur gauche i
    // & n'est pas ici l'opérateur adresse de
    int & ri{ i };
    // ri et i correspondent à la même donnée en mémoire centrale
    std::cout << "i = " << i << " - ri = " << ri << "\n";
    std::cout << "&i = " << &i << " - &ri = " << &ri << "\n";
    
    // Si une modification de cette donnée est faite via i, elle est visible via ri
    i = 5;
    std::cout << "i = " << i << " - ri = " << ri << "\n";
    
    // Si elle est faite via ri, elle est aussi visible via i
    ri = -2;
    std::cout << "i = " << i << " - ri = " << ri << "\n";
    
    int j{ 7 };
    ri = j;
    std::cout << "i = " << i << " - ri = " << ri << "\n";
    // ri reste une référence sur la valeur gauche i
    j = -1;
    std::cout << "i = " << i << " - ri = " << ri << "\n";
    
    // Donc ri n'a aucun intérêt ici puisque i peut être utilisé
    
    // Une référence sur valeur gauche peut être constante
    // Dans ce cas, elle peut être associée à une valeur droite
    const int & rk{ 8 };
    // Mais sa modification est interdite
    // rk = 5;
}
