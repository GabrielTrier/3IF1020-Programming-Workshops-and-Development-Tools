/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * Number.cpp
 */

#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>

#include "Number.hpp"

// Constructeur à partir d'un entier
Number::Number(unsigned long l) : first_(nullptr){
    if (l == 0)
    {
        first_ = new Digit(0);
    }
    else
    {
        Digit *last_digit = nullptr;
        while (l > 0)
        {
            Digit *new_digit = new Digit(l % number_base);
            l /= number_base;

            if (!first_)
            {
                first_ = new_digit;
            }
            else
            {
                last_digit->next_ = new_digit;
            }
            last_digit = new_digit;
        }
    }
}

// Constructeur de copie
Number::Number(const Number &other) : first_(nullptr){
    if (other.first_)
    {
        first_ = new Digit(other.first_->digit_);
        Digit *current_digit = first_;
        Digit *other_current_digit = other.first_->next_;
        while (other_current_digit)
        {
            current_digit->next_ = new Digit(other_current_digit->digit_);
            current_digit = current_digit->next_;
            other_current_digit = other_current_digit->next_;
        }
    }
}

// Constructeur de signature
Number::Number(std::string s) : first_(nullptr) {
    if (s.empty()) {
        throw std::invalid_argument("Chaîne vide!");
    }
    first_ = new Digit(s);// Appel du constructeur de Digit
}
//Constructeur de déplacement 
Number::Number(Number&& other) noexcept : first_(other.first_) {
    other.first_ = nullptr; 
}

// Lecture depuis un flux
std::istream& operator>>(std::istream& in, Number& n) {
    // Ignore les espaces
    in >> std::ws;
    std::string s;
    while (in.good()) {
        int c = in.get();
        if (std::isdigit(c)) {
            s += static_cast<char>(c);
        } else {
            in.putback(c);
            break;
        }
    }
    if (!s.empty()) {
        n = Number(s);  // Appel du constructeur de Number avec la chaîne
    } 
    return in;
}

// Destructeur
Number::~Number(){delete first_;}

// Méthode d'affichage
void Number::print(std::ostream &out) const
{
    if (first_)
    {
        first_->print(out);
    }
    else
    {
        out << "0";
    }
}

// Opérateur d'affectation
Number &Number::operator=(Number other){
    if (first_ && other.first_)
    {first_->swap(*other.first_);}
    else
    {std::swap(first_, other.first_);}
    return *this;
}

//Remplacement des add et multiply pour faire par rapport a des Numbers

// Surcharge de `+=` pour ajouter un entier à un `Number`
Number& Number::operator+=(unsigned int i) {
    if (first_) {
        first_->operator+=(i); // Appel de l'opération sur le premier Digit
    } else {
        first_ = new Digit(i);
    }
    return *this;
}

// Surcharge de `*=` pour multiplier un `Number` par un entier
Number& Number::operator*=(unsigned int i) {
    if (first_) {
        first_->operator*=(i);
    } else {
        first_ = new Digit(0);
    }
    return *this;
}

Number Number::operator+(const Number& other) const {
    Number result(*this); 
    Digit* current = result.first_;
    Digit* other_current = other.first_;
    
    while (other_current) {
        if (current) {
            current->operator+=(other_current->digit_);
            if (!current->next_ && other_current->next_) {
                current->next_ = new Digit();
            }
            current = current->next_;
        }
        other_current = other_current->next_;
    }
    return result;
}

Number Number::operator*(const Number& other) const {
    Number result(0);
    Digit* other_current = other.first_;
    int position = 0;

    while (other_current) {
        Number temp(*this);
        temp *= other_current->digit_;

        for (int i = 0; i < position; ++i) {
            Digit* new_digit = new Digit(0, temp.first_);
            temp.first_ = new_digit;
        }

        result = result + temp;
        other_current = other_current->next_;
        ++position;
    }
    return result;
}

// Fonction pour calculer la factorielle d'un entier
Number Number::factorial(unsigned int i) {
    Number result(1);
    for (unsigned int j = 2; j <= i; ++j) {
        result *=j;
    }
    return result;
}

/*
On remarque que les tests sont tous "passed" signifiant le bon fonctionnement!

Partie 2: Nouveau type: 

~/workspace/3if1020/tp/clp_tp2: ./TestNumber                                                            
[==========] Running 4 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 4 tests from TestNumber
[ RUN      ] TestNumber.TestNumber0
[       OK ] TestNumber.TestNumber0 (0 ms)
[ RUN      ] TestNumber.TestNumber12345678
[       OK ] TestNumber.TestNumber12345678 (0 ms)
[ RUN      ] TestNumber.TestNumberBig
[       OK ] TestNumber.TestNumberBig (0 ms)
[ RUN      ] TestNumber.TestNumberRandom
[       OK ] TestNumber.TestNumberRandom (0 ms)
[----------] 4 tests from TestNumber (0 ms total)

[----------] Global test environment tear-down
[==========] 4 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 4 tests.

Partie 3: classe concrète:

~/workspace/3if1020/tp/clp_tp2: ./TestNumber                                                            
[==========] Running 6 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 6 tests from TestNumber
[ RUN      ] TestNumber.TestNumber0
[       OK ] TestNumber.TestNumber0 (0 ms)
[ RUN      ] TestNumber.TestNumber12345678
[       OK ] TestNumber.TestNumber12345678 (0 ms)
[ RUN      ] TestNumber.TestNumberBig
[       OK ] TestNumber.TestNumberBig (0 ms)
[ RUN      ] TestNumber.TestNumberRandom
[       OK ] TestNumber.TestNumberRandom (0 ms)
[ RUN      ] TestNumber.TestCopyConstructor
[       OK ] TestNumber.TestCopyConstructor (0 ms)
[ RUN      ] TestNumber.TestAssignmentOperator
[       OK ] TestNumber.TestAssignmentOperator (0 ms)
[----------] 6 tests from TestNumber (0 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 6 tests.

Partie 4 Calculs:
Les tests ont bien était réussi signifiant une bonne implémentation des fonctions de multiplications, d'ajouts ainsi que de factorielle

~/workspace/3if1020/tp/clp_tp2: ./TestNumber                                                            
[==========] Running 11 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 11 tests from TestNumber
[ RUN      ] TestNumber.TestNumber0
[       OK ] TestNumber.TestNumber0 (0 ms)
[ RUN      ] TestNumber.TestNumber12345678
[       OK ] TestNumber.TestNumber12345678 (0 ms)
[ RUN      ] TestNumber.TestNumberBig
[       OK ] TestNumber.TestNumberBig (0 ms)
[ RUN      ] TestNumber.TestNumberRandom
[       OK ] TestNumber.TestNumberRandom (0 ms)
[ RUN      ] TestNumber.TestCopyConstructor
[       OK ] TestNumber.TestCopyConstructor (0 ms)
[ RUN      ] TestNumber.TestAssignmentOperator
[       OK ] TestNumber.TestAssignmentOperator (0 ms)
[ RUN      ] TestNumber.TestAdd
[       OK ] TestNumber.TestAdd (0 ms)
[ RUN      ] TestNumber.TestAddCarry
[       OK ] TestNumber.TestAddCarry (0 ms)
[ RUN      ] TestNumber.TestMultiply
[       OK ] TestNumber.TestMultiply (0 ms)
[ RUN      ] TestNumber.TestMultiplyCarry
[       OK ] TestNumber.TestMultiplyCarry (0 ms)
[ RUN      ] TestNumber.TestFactorial123
[       OK ] TestNumber.TestFactorial123 (3 ms)
[----------] 11 tests from TestNumber (5 ms total)

[----------] Global test environment tear-down
[==========] 11 tests from 1 test suite ran. (5 ms total)
[  PASSED  ] 11 tests.

Partie 5 : Lecture :

~/workspace/3if1020/tp/clp_tp2: ./TestNumber
[==========] Running 15 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 15 tests from TestNumber
[ RUN      ] TestNumber.TestNumber0
[       OK ] TestNumber.TestNumber0 (0 ms)
[ RUN      ] TestNumber.TestNumber12345678
[       OK ] TestNumber.TestNumber12345678 (0 ms)
[ RUN      ] TestNumber.TestNumberBig
[       OK ] TestNumber.TestNumberBig (0 ms)
[ RUN      ] TestNumber.TestNumberRandom
[       OK ] TestNumber.TestNumberRandom (0 ms)
[ RUN      ] TestNumber.TestCopyConstructor
[       OK ] TestNumber.TestCopyConstructor (0 ms)
[ RUN      ] TestNumber.TestAssignmentOperator
[       OK ] TestNumber.TestAssignmentOperator (0 ms)
[ RUN      ] TestNumber.TestAdd
[       OK ] TestNumber.TestAdd (0 ms)
[ RUN      ] TestNumber.TestAddCarry
[       OK ] TestNumber.TestAddCarry (0 ms)
[ RUN      ] TestNumber.TestMultiply
[       OK ] TestNumber.TestMultiply (0 ms)
[ RUN      ] TestNumber.TestMultiplyCarry
[       OK ] TestNumber.TestMultiplyCarry (0 ms)
[ RUN      ] TestNumber.TestFactorial123
[       OK ] TestNumber.TestFactorial123 (0 ms)
[ RUN      ] TestNumber.TestStringConstructorValid
[       OK ] TestNumber.TestStringConstructorValid (0 ms)
[ RUN      ] TestNumber.TestStringConstructorSingleDigit
[       OK ] TestNumber.TestStringConstructorSingleDigit (0 ms)
[ RUN      ] TestNumber.TestStringConstructorInvalid
[       OK ] TestNumber.TestStringConstructorInvalid (0 ms)
[ RUN      ] TestNumber.TestInputStreamOperator
[       OK ] TestNumber.TestInputStreamOperator (0 ms)
[----------] 15 tests from TestNumber (9 ms total)

[----------] Global test environment tear-down
[==========] 15 tests from 1 test suite ran. (11 ms total)
[  PASSED  ] 15 tests.

Partie 6 : Surcharge : 


~/workspace/3if1020/tp/clp_tp2: ./TestNumber                                                            
[==========] Running 17 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 17 tests from TestNumber
[ RUN      ] TestNumber.TestNumber0
[       OK ] TestNumber.TestNumber0 (1 ms)
[ RUN      ] TestNumber.TestNumber12345678
[       OK ] TestNumber.TestNumber12345678 (0 ms)
[ RUN      ] TestNumber.TestNumberBig
[       OK ] TestNumber.TestNumberBig (0 ms)
[ RUN      ] TestNumber.TestNumberRandom
[       OK ] TestNumber.TestNumberRandom (0 ms)
[ RUN      ] TestNumber.TestCopyConstructor
[       OK ] TestNumber.TestCopyConstructor (0 ms)
[ RUN      ] TestNumber.TestAssignmentOperator
[       OK ] TestNumber.TestAssignmentOperator (0 ms)
[ RUN      ] TestNumber.TestAdd
[       OK ] TestNumber.TestAdd (0 ms)
[ RUN      ] TestNumber.TestAddCarry
[       OK ] TestNumber.TestAddCarry (0 ms)
[ RUN      ] TestNumber.TestMultiply
[       OK ] TestNumber.TestMultiply (0 ms)
[ RUN      ] TestNumber.TestMultiplyCarry
[       OK ] TestNumber.TestMultiplyCarry (0 ms)
[ RUN      ] TestNumber.TestFactorial123
[       OK ] TestNumber.TestFactorial123 (0 ms)
[ RUN      ] TestNumber.TestStringConstructorValid
[       OK ] TestNumber.TestStringConstructorValid (0 ms)
[ RUN      ] TestNumber.TestStringConstructorSingleDigit
[       OK ] TestNumber.TestStringConstructorSingleDigit (0 ms)
[ RUN      ] TestNumber.TestStringConstructorInvalid
[       OK ] TestNumber.TestStringConstructorInvalid (0 ms)
[ RUN      ] TestNumber.TestInputStreamOperator
[       OK ] TestNumber.TestInputStreamOperator (0 ms)
[ RUN      ] TestNumber.TestMoveConstructor
[       OK ] TestNumber.TestMoveConstructor (0 ms)
[ RUN      ] TestNumber.TestMoveAssignment
[       OK ] TestNumber.TestMoveAssignment (0 ms)
[----------] 17 tests from TestNumber (6 ms total)

[----------] Global test environment tear-down
[==========] 17 tests from 1 test suite ran. (7 ms total)
[  PASSED  ] 17 tests.
*/