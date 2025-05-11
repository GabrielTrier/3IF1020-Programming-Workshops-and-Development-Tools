/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * TestExpression.cpp
 * c++ -std=c++20 -o TestExpression TestExpression.cpp Expression.cpp -lgtest -lpthread
 */

#include <sstream>
#include <utility>

#include <gtest/gtest.h>

#include "Expression.hpp"

void check_display(const Expression& expr, const std::string& expected) {
    std::ostringstream oss;
    oss << expr;
    EXPECT_EQ(oss.str(), expected);
}

// Test unitaire pour l'affichage d'un nombre
TEST(ExpressionDisplayTest, NombreDisplay) {
    Nombre num(5.0);
    check_display(num, "5.0");
}

// Test unitaire pour l'affichage d'une variable
TEST(ExpressionDisplayTest, VariableDisplay) {
    Variable var("x");
    check_display(var, "x");
}

// Test pour la dérivation d'un Nombre
TEST(ExpressionDerivationTest, NombreDerive) {
    Nombre num(15.0);
    Expression* derived = num.derive("x");
    check_display(*derived, "0.0");
    delete derived;
}

// Test pour la dérivation d'une Variable par rapport à elle-même
TEST(ExpressionDerivationTest, VariableDeriveSame) {
    Variable var("x");
    Expression* derived = var.derive("x");
    check_display(*derived, "1.0");
    delete derived;
}

// Test pour la dérivation d'une Variable par rapport à une autre variable
TEST(ExpressionDerivationTest, VariableDeriveDifferent) {
    Variable var("x");
    Expression* derived = var.derive("y");
    check_display(*derived, "0.0");
    delete derived;
}

// Test pour l'affichage d'une addition
TEST(ExpressionDisplayTest, AdditionDisplay) {
    Expression* num1 = new Nombre(13.0);
    Expression* num2 = new Nombre(15.0);
    Expression* add = new Addition(num1, num2);
    check_display(*add, "(13.0 + 15.0)");
    delete add; 
}

//Test pour la dérivation d'une addition
TEST(ExpressionDerivationTest, AdditionDerive) {
    Expression* var1 = new Variable("x");
    Expression* var2 = new Variable("y");
    Expression* add = new Addition(var1, var2);
    Expression* derived = add->derive("x");
    check_display(*derived, "(1.0 + 0.0)");
    delete add;
    delete derived;
}

// Test pour l'affichage d'une multiplication
TEST(ExpressionDisplayTest, MultiplicationDisplay) {
    Expression* num1 = new Nombre(13.0);
    Expression* num2 = new Nombre(15.0);
    Expression* mult = new Multiplication(num1, num2);
    check_display(*mult, "(13.0 * 15.0)");
    delete mult;
}

// Test pour la dérivation d'une multiplication
TEST(ExpressionDerivationTest, MultiplicationDerive) {
    Expression* var1 = new Variable("x");
    Expression* var2 = new Variable("y");
    Expression* mult = new Multiplication(var1, var2);
    Expression* derived = mult->derive("x");
    check_display(*derived, "((1.0 * y) + (x * 0.0))");
    delete mult;
    delete derived;
}

// Test addition de deux nombres
TEST(ExpressionSimplifyTest, AdditionOfNumbersSimplify) {
    Expression* num1 = new Nombre(10.0);
    Expression* num2 = new Nombre(4.0);
    Expression* add = new Addition(num1, num2);
    Expression* simplified = add->simplify();
    check_display(*simplified, "14.0");
    delete add;
    delete simplified; 
}
// Test addition opérande gauche = 0
TEST(ExpressionSimplifyTest, AdditionWithZeroLeftSimplify) {
    Expression* zero = new Nombre(0.0);
    Expression* var = new Variable("x");
    Expression* add = new Addition(zero, var);
    Expression* simplified = add->simplify();
    check_display(*simplified, "x");
    delete add;
    delete simplified;
}

// Test addition droit = 0
TEST(ExpressionSimplifyTest, AdditionWithZeroRightSimplify) {
    Expression* var = new Variable("x");
    Expression* zero = new Nombre(0.0);
    Expression* add = new Addition(var, zero);
    Expression* simplified = add->simplify();
    check_display(*simplified, "x");
    delete add;
    delete simplified;
}

// Test multiplication de 2 nombres
TEST(ExpressionSimplifyTest, MultiplicationOfNumbersSimplify) {
    Expression* num1 = new Nombre(3.0);
    Expression* num2 = new Nombre(4.0);
    Expression* mult = new Multiplication(num1, num2);
    Expression* simplified = mult->simplify();
    check_display(*simplified, "12.0");
    delete mult;
    delete simplified;
}
// Test multiplication par 1 à gauche 
TEST(ExpressionSimplifyTest, MultiplicationWithOneLeftSimplify) {
    Expression* one = new Nombre(1.0);
    Expression* var = new Variable("x");
    Expression* mult = new Multiplication(one, var);
    Expression* simplified = mult->simplify();
    check_display(*simplified, "x");
    delete mult;
    delete simplified;
}

// Test similaire pour l'autre opérande
TEST(ExpressionSimplifyTest, MultiplicationWithOneRightSimplify) {
    Expression* var = new Variable("x");
    Expression* one = new Nombre(1.0);
    Expression* mult = new Multiplication(var, one);
    Expression* simplified = mult->simplify();
    check_display(*simplified, "x");
    delete mult;
    delete simplified;
}

// Test multiplication par 0 à gauche
TEST(ExpressionSimplifyTest, MultiplicationWithZeroLeftSimplify) {
    Expression* zero = new Nombre(0.0);
    Expression* var = new Variable("x");
    Expression* mult = new Multiplication(zero, var);
    Expression* simplified = mult->simplify();
    check_display(*simplified, "0.0");
    delete mult;
    delete simplified;
}

// Test mais pour opérande de droite 
TEST(ExpressionSimplifyTest, MultiplicationWithZeroRightSimplify) {
    Expression* var = new Variable("x");
    Expression* zero = new Nombre(0.0);
    Expression* mult = new Multiplication(var, zero);
    Expression* simplified = mult->simplify();
    check_display(*simplified, "0.0");
    delete mult;
    delete simplified;
}


int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    int tests = RUN_ALL_TESTS();
    std::cout << "Nbr instances créées: " << Expression::getInstanceCount() << std::endl;
    std::cout << "Nbr instances détruites: " << Expression::getDestroyedCount() << std::endl;
    return tests;
}
