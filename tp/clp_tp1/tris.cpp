/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * tris.cpp
 */

#include <iostream>
#include <vector>
#include <utility>
#include <functional>

#include <cstdlib>
#include <ctime>

// Fonction pour afficher un tableau d'entiers sur la sortie standard
void print_tab(const std::vector<int> &tab)
{
    std::cout << "[ ";
    for (const int &num : tab)
    {
        std::cout << num << " ";
    }
    std::cout << "]" << std::endl;
}
// Fonction pour générer un tableau d'entiers aléatoires entre -10 et 10
void random_tab(std::vector<int> &tab)
{
    std::srand(std::time(0));
    for (int &num : tab)
    {
        num = std::rand() % 21 - 10;
    }
}
// Fonction pour trier un tableau par odre croissant avec la méthode de tri par sélection
void sort_tab_1(std::vector<int> &tab)
{
    int n = tab.size();
    for (int i = 0; i < n - 1; ++i)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (tab[j] < tab[min_idx])
            {
                min_idx = j;
            }
        }
        std::swap(tab[i], tab[min_idx]);
    }
}
// Fonction de comparaison pour vérifier si le premier entier est inférieur au second
bool less(int a, int b)
{
    return a < b;
}
//Fonction de comparaison pour vérifier si le premier entier est supérieur au second
bool greater(int a, int b)
{
    return a > b;
}
//Fonction pour trier un tableau par ordre croissant ou décroissant 
void sort_tab_2(std::vector<int> &tab, bool (*compare)(int, int))
{
    int n = tab.size();
    for (int i = 0; i < n - 1; ++i)
    {
        int selected_idx = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (compare(tab[j], tab[selected_idx]))
            {
                selected_idx = j;
            }
        }
        std::swap(tab[i], tab[selected_idx]);
    }
}
// Fonction pour trier un tableau par ordre croissant ou décroissant avec une fonction lambda
void sort_tab_3(std::vector<int> &tab, std::function<bool(int, int)> compare)
{
    int n = tab.size();
    for (int i = 0; i < n - 1; ++i)
    {
        int selected_idx = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (compare(tab[j], tab[selected_idx]))
            {
                selected_idx = j;
            }
        }
        std::swap(tab[i], tab[selected_idx]);
    }
}
// Fonction pour générer un tableau d'entiers aléatoires
void test_11()
{
    std::cout << "*** test_11 ***" << std::endl;
    const std::vector<int> tab{1, -2, 3, -4, 5, -6};
    print_tab(tab);
}
// Function pour tester la génération d'un tableau d'entiers aléatoires
void test_12()
{
    std::cout << "*** test_12 ***" << std::endl;
    std::vector<int> tab(10);
    random_tab(tab);
    print_tab(tab);
}
// Fonction pour tester le tri d'un tableau d'entiers aléatoires par ordre croissant
void test_13()
{
    std::cout << "*** test_13 ***" << std::endl;
    std::vector<int> tab(10);
    random_tab(tab);
    std::cout << "Tableau avant tri" << std::endl;
    print_tab(tab);
    std::cout << "Tableau après tri par sélection" << std::endl;
    sort_tab_1(tab);
    print_tab(tab);
}
 // Fonction pour tester la version 2 de la fonction de tri
void test_14(){
    std::cout << "*** test_14 ***" << std::endl;
    std::vector<int> tab(10);
    random_tab(tab);
    std::cout << "Tableau avant tri" << std::endl;
    print_tab(tab);
    std::cout << "Tableau après tri croissant" << std::endl;
    sort_tab_2(tab, less);
    print_tab(tab);
    std::cout << "Tableau après tri décroissant" << std::endl;
    sort_tab_2(tab, greater);
    print_tab(tab);
}
// Fonction pour tester la version 3 de la fonction de tri avec une fonction lambda
void test_15()
{
    std::cout << "*** test_15 ***" << std::endl;
    std::vector<int> tab(10);
    random_tab(tab);
    std::cout << "Tableau avant tri" << std::endl;
    print_tab(tab);
    std::cout << "Tableau après tri croissant par valeur absolue" << std::endl;
    sort_tab_3(tab, [](int a, int b)
               { return std::abs(a) < std::abs(b); });
    print_tab(tab);
    std::cout << "Tableau après tri décroissant par valeur absolue" << std::endl;
    sort_tab_3(tab, [](int a, int b)
               { return std::abs(a) > std::abs(b); });
    print_tab(tab);
}

int main()
{
    std::srand( std::time( nullptr ));
    //test_11();
    //test_12();
    //test_13();
    //test_14();
    test_15();
    return 0;
}