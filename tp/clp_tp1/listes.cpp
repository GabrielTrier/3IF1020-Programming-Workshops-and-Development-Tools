/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * listes.cpp
 */

#include <iostream>
#include <forward_list>
#include <functional>
#include <limits>

#include <cstdlib>
#include <ctime>

// Type liste unidirectionnelle d'entiers
using int_list_t = std::forward_list<int>;
using int_list_iter_t = int_list_t::const_iterator;

// Fonction pour générer une liste d'entiers aléatoires et retourner un nombre aléatoire d'éléments
int_list_t random_list()
{
    int_list_t list;
    int num_elements = std::rand() % 10; // Nombre aléatoire d'éléments entre 0 et 9
    for (int i = 0; i < num_elements; ++i)
    {
        list.push_front(std::rand() % 100); // Valeur aléatoire entre 0 et 99
    }
    return list;
}

// Fonction pour afficher une liste d'entiers
void print_list(const int_list_t &list)
{
    std::cout << "( ";
    for (const int &num : list)
    {
        std::cout << num << " ";
    }
    std::cout << ")" << std::endl;
}

// Fonction pour appliquer une fonction lambda à une liste d'entiers
int_list_t map_iter(const int_list_t &list, std::function<int(int)> func)
{
    int_list_t result;
    for (const int &num : list)
    {
        result.push_front(func(num));
    }
    return result;
}

// Fonction pour filtrer une liste d'entiers en fonction d'un prédicat
int_list_t filter_iter(const int_list_t &list, std::function<bool(int)> pred)
{
    int_list_t result;
    for (const int &num : list)
    {
        if (pred(num))
        {
            result.push_front(num);
        }
    }
    return result;
}

// Fonction pour réduire une liste d'entiers à un seul entier en appliquant une fonction
int reduce(const int_list_t &list, int init, std::function<int(int, int)> func)
{
    for (const int &num : list)
    {
        init = func(init, num);
    }
    return init;
}

// Fonction auxiliaire récursive pour fold_left
int fold_left_aux(int_list_iter_t current, int_list_iter_t end, int acc, std::function<int(int, int)> func)
{
    // Si on a atteint la fin de la liste on retourne l'accumulateur
    if (current == end)
    {
        return acc;
    }
    // Appel récursif après application de la fonction de réduction
    return fold_left_aux(std::next(current), end, func(acc, *current), func);
}

// Fonction d'appel pour fold_left_aux avec un itérateur de début et de fin de liste
int fold_left(const int_list_t &list, int init, std::function<int(int, int)> func)
{
    return fold_left_aux(list.cbegin(), list.cend(), init, func);
}

// Version récursive pour fonction map()
int_list_t map_aux(int_list_iter_t current, int_list_iter_t end, std::function<int(int)> func)
{
    if (current == end)
    {
        return int_list_t(); // Retourne une liste vide permettant de ne pas avoir à inverser la liste à la fin
    }
    else
    {
        int_list_t result = map_aux(std::next(current), end, func);
        result.push_front(func(*current));
        return result;
    }
}

int_list_t map(const int_list_t &list, std::function<int(int)> func)
{
    return map_aux(list.cbegin(), list.cend(), func);
}

// Version récursive pour fonction filter()
int_list_t filter_aux(int_list_iter_t current, int_list_iter_t end, std::function<bool(int)> pred)
{
    if (current == end)
    {
        return int_list_t(); // Même principe que pour map_aux afin d'éviter l'inversement des éléments
    }
    else
    {
        int_list_t result = filter_aux(std::next(current), end, pred);
        if (pred(*current))
        {
            result.push_front(*current);
        }
        return result;
    }
}

int_list_t filter(const int_list_t &list, std::function<bool(int)> pred)
{
    return filter_aux(list.cbegin(), list.cend(), pred);
}


// Fonction pour tester la génération d'une liste d'entiers aléatoires
void test_21()
{
    std::cout << "*** test_21 ***" << std::endl;
    int_list_t list = random_list();
    print_list(list);
}

// Fonction pour tester l'application d'une fonction lambda à une liste d'entiers
void test_22()
{
    std::cout << "*** test_22 ***" << std::endl;
    int_list_t list = random_list();
    std::cout << "Liste initiale" << std::endl;
    print_list(list);
    int_list_t result = map_iter(list, [](int x)
                                 { return x * 3; });
    std::cout << "Liste après application de la fonction lambda (3x)" << std::endl;
    print_list(result);
}

// Fonction pour tester l'application de map_iter et filter_iter à une liste d'entiers
void test_23()
{
    std::cout << "*** test_23 ***" << std::endl;
    int_list_t list = random_list();
    std::cout << "Liste initiale" << std::endl;
    print_list(list);
    int_list_t mapped_list = map_iter(list, [](int x)
                                      { return x * 3; });
    std::cout << "Liste après application de la fonction lambda (3x)" << std::endl;
    print_list(mapped_list);
    int_list_t filtered_list = filter_iter(mapped_list, [](int x)
                                           { return x % 2 == 0; });
    std::cout << "Liste pour ne garder uniquement que les éléments pairs" << std::endl;
    print_list(filtered_list);
}

// Fonction pour tester l'application de map_iter et filter_iter à une liste d'entiers avec un coefficient aléatoire
void test_24()
{
    std::cout << "*** test_24 ***" << std::endl;
    int_list_t list = random_list();
    std::cout << "Liste initiale" << std::endl;
    print_list(list);

    int coefficient = std::rand() % 5 + 1;
    int_list_t mapped_list = map_iter(list, [coefficient](int x)
                                      { return x * coefficient; });

    std::cout << "Liste après application de la fonction lambda avec coeff aléatoire = " << coefficient<< std::endl;
    print_list(mapped_list);

    int_list_t filtered_list = filter_iter(mapped_list, [](int x)
                                           { return x % 2 == 0; });
    std::cout << "Liste pour ne garder uniquement que les éléments pairs" << std::endl;
    print_list(filtered_list);
}

// Fonction pour tester la réduction d'une liste d'entiers
void test_25()
{
    std::cout << "*** test_25 ***" << std::endl;
    int_list_t list = random_list();
    std::cout << "Liste initiale" << std::endl;
    print_list(list);
    std::cout << "Plus petit élément: " << reduce(list, std::numeric_limits<int>::max(), [](int a, int b)
                           { return std::min(a, b); }) <<std::endl;
    std::cout << "Plus grand élément: " << reduce(list, std::numeric_limits<int>::min(), [](int a, int b)
                           { return std::max(a, b); }) << std::endl;
}

// Fonction pour tester la version récursive
void test_31()
{
    std::cout << "*** test_31 ***" << std::endl;
    int_list_t list = random_list();
    std::cout << "Liste initiale" << std::endl;
    print_list(list);
    std::cout << "Plus petit élément: " << fold_left(list, std::numeric_limits<int>::max(), [](int a, int b)
                            { return std::min(a, b); }) << std::endl;
    std::cout << "Plus grand élément: " << fold_left(list, std::numeric_limits<int>::min(), [](int a, int b)
                            { return std::max(a, b); }) << std::endl;
}

// Fonction pour tester l'application de récurvsive de map et filter à une liste d'entiers avec un coefficient aléatoire
void test_32()
{
    std::cout << "*** test_32 ***" << std::endl;
    int_list_t list = random_list();
    std::cout << "Liste initiale" << std::endl;
    print_list(list);

    int coefficient = std::rand() % 5 + 1;
    int_list_t mapped_list = map(list, [coefficient](int x)
                                 { return x * coefficient; });

    std::cout << "Liste après application de la fonction lambda avec coeff aléatoire = " << coefficient << std::endl;
    print_list(mapped_list);

    int_list_t filtered_list = filter(mapped_list, [](int x)
                                      { return x % 2 == 0; });
    std::cout << "Liste pour ne garder uniquement que les éléments pairs" << std::endl;
    print_list(filtered_list);
}

int main()
{
    std::srand( std::time( nullptr ));
    //test_21();
    //test_22();
    //test_23();
    //test_24();
    //test_25();
    //test_31();
    test_32();
    return 0;
}