/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * TestSmartExpression.cpp
 * Compilation : c++ -std=c++20 -o TestSmartExpression TestSmartExpression.cpp SmartExpression.cpp -lgtest -lpthread
 */

#include <sstream>
#include <memory>

#include <gtest/gtest.h>

#include "SmartExpression.hpp"

void check_display(const SmartExpression& expr, const std::string& expected) {
    std::ostringstream oss;
    oss << expr;
    EXPECT_EQ(oss.str(), expected);
}

// Test unitaire pour l'affichage d'un nombre
TEST(SmartExpressionDisplayTest, NombreDisplay) {
    auto num = std::make_shared<SmartNombre>(5.0f);
    check_display(*num, "5.0");
}

// Test unitaire pour l'affichage d'une variable
TEST(SmartExpressionDisplayTest, VariableDisplay) {
    auto var = std::make_shared<SmartVariable>("x");
    check_display(*var, "x");
}

// Test pour l'affichage d'une addition
TEST(SmartExpressionDisplayTest, AdditionDisplay) {
    auto num1 = std::make_shared<SmartNombre>(13.0f);
    auto num2 = std::make_shared<SmartNombre>(15.0f);
    auto add = std::make_shared<SmartAddition>(num1, num2);
    check_display(*add, "(13.0 + 15.0)");
}

// Test pour l'affichage d'une multiplication
TEST(SmartExpressionDisplayTest, MultiplicationDisplay) {
    auto num1 = std::make_shared<SmartNombre>(13.0f);
    auto num2 = std::make_shared<SmartNombre>(15.0f);
    auto mult = std::make_shared<SmartMultiplication>(num1, num2);
    check_display(*mult, "(13.0 * 15.0)");
}

// Test pour la dérivation d'un nombre
TEST(SmartExpressionDerivationTest, NombreDerive) {
    auto num = std::make_shared<SmartNombre>(5.0f);
    auto derived = num->derive("x");
    auto derived_num = std::dynamic_pointer_cast<SmartNombre>(derived);
    ASSERT_TRUE(derived_num != nullptr);
    EXPECT_EQ(derived_num->compute(), 0.0f);
}

// Test pour la dérivation d'une variable
TEST(SmartExpressionDerivationTest, VariableDeriveSame) {
    auto var = std::make_shared<SmartVariable>("x");
    auto derived = var->derive("x");
    auto derived_num = std::dynamic_pointer_cast<SmartNombre>(derived);
    ASSERT_TRUE(derived_num != nullptr);
    EXPECT_EQ(derived_num->compute(), 1.0f);
}

// Test pour la dérivation d'une variable différente
TEST(SmartExpressionDerivationTest, VariableDeriveDifferent) {
    auto var = std::make_shared<SmartVariable>("x");
    auto derived = var->derive("y");
    auto derived_num = std::dynamic_pointer_cast<SmartNombre>(derived);
    ASSERT_TRUE(derived_num != nullptr);
    EXPECT_EQ(derived_num->compute(), 0.0f);
}

// Test pour la simplification d'une addition
TEST(SmartExpressionSimplifyTest, SimplifyAddition) {
    auto num1 = std::make_shared<SmartNombre>(5.0f);
    auto num2 = std::make_shared<SmartNombre>(3.0f);
    auto addition = std::make_shared<SmartAddition>(num1, num2);
    auto simplified = addition->simplify();
    auto simplified_num = std::dynamic_pointer_cast<SmartNombre>(simplified);
    ASSERT_TRUE(simplified_num != nullptr);
    EXPECT_EQ(simplified_num->compute(), 8.0f);
}

// Test pour la simplification d'une multiplication
TEST(SmartExpressionSimplifyTest, SimplifyMultiplication) {
    auto num1 = std::make_shared<SmartNombre>(0.0f);
    auto num2 = std::make_shared<SmartNombre>(5.0f);
    auto multiplication = std::make_shared<SmartMultiplication>(num1, num2);
    auto simplified = multiplication->simplify();
    auto simplified_num = std::dynamic_pointer_cast<SmartNombre>(simplified);
    ASSERT_TRUE(simplified_num != nullptr);
    EXPECT_EQ(simplified_num->compute(), 0.0f);
}

// Test pour la dérivation d'une addition
TEST(SmartExpressionDerivationTest, AdditionDerive) {
    auto var1 = std::make_shared<SmartVariable>("x");
    auto var2 = std::make_shared<SmartVariable>("y");
    auto add = std::make_shared<SmartAddition>(var1, var2);
    auto derived = add->derive("x");
    check_display(*derived, "(1.0 + 0.0)");
}

// Test pour la dérivation d'une multiplication
TEST(SmartExpressionDerivationTest, MultiplicationDerive) {
    auto var1 = std::make_shared<SmartVariable>("x");
    auto var2 = std::make_shared<SmartVariable>("y");
    auto mult = std::make_shared<SmartMultiplication>(var1, var2);
    auto derived = mult->derive("x");
    check_display(*derived, "((1.0 * y) + (x * 0.0))");
}

// Test pour la simplification d'une expression complexe
TEST(SmartExpressionSimplifyTest, SimplifyComplexExpression) {
    auto num0 = std::make_shared<SmartNombre>(0.0f);
    auto num1 = std::make_shared<SmartNombre>(1.0f);
    auto var = std::make_shared<SmartVariable>("x");
    auto addition = std::make_shared<SmartAddition>(num0, var);
    auto multiplication = std::make_shared<SmartMultiplication>(num1, addition);
    auto simplified = multiplication->simplify();
    check_display(*simplified, "x");
}

// Test pour comparer le nombre d'instances créées lors de la dérivation et de la simplification
TEST(SmartExpressionInstanceCountTest, CompareInstanceCount) {
    auto var = std::make_shared<SmartVariable>("x");
    auto num = std::make_shared<SmartNombre>(2.0f);
    auto add = std::make_shared<SmartAddition>(var, num);
    auto mult = std::make_shared<SmartMultiplication>(add, var);

    int initial_created = SmartExpression::getInstanceCount();
    int initial_destroyed = SmartExpression::getDestroyedCount();

    auto derived = mult->derive("x");
    auto simplified = mult->simplify();

    int final_created = SmartExpression::getInstanceCount();
    int final_destroyed = SmartExpression::getDestroyedCount();

    std::cout << "Instances créées (dérivation): " << final_created - initial_created << std::endl;
    std::cout << "Instances détruites (dérivation): " << final_destroyed - initial_destroyed << std::endl;

    initial_created = final_created;
    initial_destroyed = final_destroyed;

    simplified = mult->simplify();

    final_created = SmartExpression::getInstanceCount();
    final_destroyed = SmartExpression::getDestroyedCount();

    std::cout << "Instances créées (simplification): " << final_created - initial_created << std::endl;
    std::cout << "Instances détruites (simplification): " << final_destroyed - initial_destroyed << std::endl;
}

int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    int tests = RUN_ALL_TESTS();

    //Forcer la destruction des instances statiques
    SmartExpression::zero.reset();
    SmartExpression::one.reset();

    std::cout << "Nbr instances créées: " << SmartExpression::getInstanceCount() << std::endl;
    std::cout << "Nbr instances détruites: " << SmartExpression::getDestroyedCount() << std::endl;
    return tests;
}
