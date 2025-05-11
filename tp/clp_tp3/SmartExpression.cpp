/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * SmartExpression.cpp
 */

#include <iostream>
#include <string>
#include <utility>
#include <memory>
#include <iomanip>

#include "SmartExpression.hpp"

/*Init statiques */

int SmartExpression::count_created = 0;
int SmartExpression::count_destroyed = 0;

std::shared_ptr<SmartNombre> SmartExpression::zero = std::make_shared<SmartNombre>(0.0f);
std::shared_ptr<SmartNombre> SmartExpression::one = std::make_shared<SmartNombre>(1.0f);

/*Smart Expression*/

SmartExpression::SmartExpression() {}

SmartExpression::~SmartExpression() {
    ++count_destroyed;
}

/*Smart Nombre*/
SmartNombre::SmartNombre(float value): value_(value) {++count_created;}

SmartNombre::SmartNombre(const SmartNombre& other): value_(other.value_) {++count_created;}

std::shared_ptr<SmartExpression> SmartNombre::simplify() const {
    return std::const_pointer_cast<SmartExpression>(shared_from_this());
}

std::shared_ptr<SmartExpression> SmartNombre::derive(const std::string&) const {return SmartExpression::zero;}

float SmartNombre::compute() const {return value_;}

//Format spécifique pour tests
void SmartNombre::print(std::ostream& os) const {
    // Sauvegarder format actuel du flux
    std::ios::fmtflags f(os.flags());
    os << std::fixed << std::setprecision(1) << value_;
    // Restauration fromat de flux
    os.flags(f);
}

/*Sart Variable*/
SmartVariable::SmartVariable(const std::string& name): name_(name) {++count_created;}

SmartVariable::SmartVariable(const SmartVariable& other): name_(other.name_) {++count_created;}

std::shared_ptr<SmartExpression> SmartVariable::simplify() const {
    return std::const_pointer_cast<SmartExpression>(shared_from_this());
}

std::shared_ptr<SmartExpression> SmartVariable::derive(const std::string& variable_name) const {
    return (name_ == variable_name) ? SmartExpression::one : SmartExpression::zero;
}

float SmartVariable::compute() const {
    throw std::runtime_error("Pas de valeur!");
}

void SmartVariable::print(std::ostream& os) const {
    os << name_;
}

/*Smart Operation*/
SmartOperation::SmartOperation(std::shared_ptr<SmartExpression> left, std::shared_ptr<SmartExpression> right)
    : left_operand_(std::move(left)), right_operand_(std::move(right)) {
    ++count_created;
}

SmartOperation::SmartOperation(const SmartOperation& other)
    : left_operand_(other.left_operand_), right_operand_(other.right_operand_) {
    ++count_created;
}
/*Smart Addition*/
std::shared_ptr<SmartExpression> SmartAddition::simplify() const {
    auto simplified_left = left_operand_->simplify();
    auto simplified_right = right_operand_->simplify();

    auto left_num = std::dynamic_pointer_cast<SmartNombre>(simplified_left);
    auto right_num = std::dynamic_pointer_cast<SmartNombre>(simplified_right);

    if (left_num && right_num) {
        // Si les deux opérandes sont des nombres, on calcule la somme
        return std::make_shared<SmartNombre>(left_num->compute() + right_num->compute());
    }
    if (left_num && left_num->compute() == 0.0f) {
        // Si le gauche est zéro, on retourne le droit
        return simplified_right;
    }
    if (right_num && right_num->compute() == 0.0f) {
        // Si le droit est zéro, on retourne la gauche
        return simplified_left;
    }
    // Sinon, on retourne une nouvelle addition simplifiée
    return std::make_shared<SmartAddition>(simplified_left, simplified_right);
}

std::shared_ptr<SmartExpression> SmartAddition::derive(const std::string& variable_name) const {
    return std::make_shared<SmartAddition>(
        left_operand_->derive(variable_name),
        right_operand_->derive(variable_name)
    );
}

float SmartAddition::compute() const {
    return left_operand_->compute() + right_operand_->compute();
}

void SmartAddition::print(std::ostream& os) const {
    os << "(" << *left_operand_ << " + " << *right_operand_ << ")";
}

/*Smart multiplication*/
std::shared_ptr<SmartExpression> SmartMultiplication::simplify() const {
    auto simplified_left = left_operand_->simplify();
    auto simplified_right = right_operand_->simplify();

    auto left_num = std::dynamic_pointer_cast<SmartNombre>(simplified_left);
    auto right_num = std::dynamic_pointer_cast<SmartNombre>(simplified_right);

    if (left_num && right_num) {
        // Si les deux opérandes sont des nombres, on calcule le produit
        return std::make_shared<SmartNombre>(left_num->compute() * right_num->compute());
    }
    if ((left_num && left_num->compute() == 0.0f) ||
        (right_num && right_num->compute() == 0.0f)) {
        // Si l'un des opérandes est zéro, le résultat est zéro
        return zero;
    }
    if (left_num && left_num->compute() == 1.0f) {
        // Si le gauche est un, on retourne le droit
        return simplified_right;
    }
    if (right_num && right_num->compute() == 1.0f) {
        // Si le droit est un, on retourne la gauche
        return simplified_left;
    }
    return std::make_shared<SmartMultiplication>(simplified_left, simplified_right);
}

std::shared_ptr<SmartExpression> SmartMultiplication::derive(const std::string& variable_name) const {
    return std::make_shared<SmartAddition>(
        std::make_shared<SmartMultiplication>(
            left_operand_->derive(variable_name),
            right_operand_
        ),
        std::make_shared<SmartMultiplication>(
            left_operand_,
            right_operand_->derive(variable_name)
        )
    );
}

float SmartMultiplication::compute() const {
    return left_operand_->compute() * right_operand_->compute();
}

void SmartMultiplication::print(std::ostream& os) const {
    os << "(" << *left_operand_ << " * " << *right_operand_ << ")";
}

/* Pour cette partie avancée, nous avons remplacé les pointeurs bruts par des std::shared_ptr<SmartExpression>. 
Cela permet de bénéficier de la gestion automatique de la mémoire offerte par les pointeurs intelligents.
Donc évitant ainsi des fuites de mémoire! 

~/workspace/3if1020/tp/clp_tp3: ./TestSmartExpression                                                                              
[==========] Running 12 tests from 3 test suites.
[----------] Global test environment set-up.
[----------] 4 tests from SmartExpressionDisplayTest
[ RUN      ] SmartExpressionDisplayTest.NombreDisplay
[       OK ] SmartExpressionDisplayTest.NombreDisplay (0 ms)
[ RUN      ] SmartExpressionDisplayTest.VariableDisplay
[       OK ] SmartExpressionDisplayTest.VariableDisplay (0 ms)
[ RUN      ] SmartExpressionDisplayTest.AdditionDisplay
[       OK ] SmartExpressionDisplayTest.AdditionDisplay (0 ms)
[ RUN      ] SmartExpressionDisplayTest.MultiplicationDisplay
[       OK ] SmartExpressionDisplayTest.MultiplicationDisplay (0 ms)
[----------] 4 tests from SmartExpressionDisplayTest (0 ms total)

[----------] 5 tests from SmartExpressionDerivationTest
[ RUN      ] SmartExpressionDerivationTest.NombreDerive
[       OK ] SmartExpressionDerivationTest.NombreDerive (0 ms)
[ RUN      ] SmartExpressionDerivationTest.VariableDeriveSame
[       OK ] SmartExpressionDerivationTest.VariableDeriveSame (0 ms)
[ RUN      ] SmartExpressionDerivationTest.VariableDeriveDifferent
[       OK ] SmartExpressionDerivationTest.VariableDeriveDifferent (0 ms)
[ RUN      ] SmartExpressionDerivationTest.AdditionDerive
[       OK ] SmartExpressionDerivationTest.AdditionDerive (0 ms)
[ RUN      ] SmartExpressionDerivationTest.MultiplicationDerive
[       OK ] SmartExpressionDerivationTest.MultiplicationDerive (0 ms)
[----------] 5 tests from SmartExpressionDerivationTest (0 ms total)

[----------] 3 tests from SmartExpressionSimplifyTest
[ RUN      ] SmartExpressionSimplifyTest.SimplifyAddition
[       OK ] SmartExpressionSimplifyTest.SimplifyAddition (0 ms)
[ RUN      ] SmartExpressionSimplifyTest.SimplifyMultiplication
[       OK ] SmartExpressionSimplifyTest.SimplifyMultiplication (0 ms)
[ RUN      ] SmartExpressionSimplifyTest.SimplifyComplexExpression
[       OK ] SmartExpressionSimplifyTest.SimplifyComplexExpression (0 ms)
[----------] 3 tests from SmartExpressionSimplifyTest (0 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 3 test suites ran. (0 ms total)
[  PASSED  ] 12 tests.*/

/* On utilise des instances statiques partagées pour les valeurs 0 et 1
afin d'éviter de créer de nouvelles instances à chaque dérivation d'un nombre ou d'une variable!

~/workspace/3if1020/tp/clp_tp3: ./TestSmartExpression
[==========] Running 12 tests from 3 test suites.
[----------] Global test environment set-up.
[----------] 4 tests from SmartExpressionDisplayTest
[ RUN      ] SmartExpressionDisplayTest.NombreDisplay
[       OK ] SmartExpressionDisplayTest.NombreDisplay (0 ms)
[ RUN      ] SmartExpressionDisplayTest.VariableDisplay
[       OK ] SmartExpressionDisplayTest.VariableDisplay (0 ms)
[ RUN      ] SmartExpressionDisplayTest.AdditionDisplay
[       OK ] SmartExpressionDisplayTest.AdditionDisplay (0 ms)
[ RUN      ] SmartExpressionDisplayTest.MultiplicationDisplay
[       OK ] SmartExpressionDisplayTest.MultiplicationDisplay (0 ms)
[----------] 4 tests from SmartExpressionDisplayTest (1 ms total)

[----------] 5 tests from SmartExpressionDerivationTest
[ RUN      ] SmartExpressionDerivationTest.NombreDerive
[       OK ] SmartExpressionDerivationTest.NombreDerive (0 ms)
[ RUN      ] SmartExpressionDerivationTest.VariableDeriveSame
[       OK ] SmartExpressionDerivationTest.VariableDeriveSame (0 ms)
[ RUN      ] SmartExpressionDerivationTest.VariableDeriveDifferent
[       OK ] SmartExpressionDerivationTest.VariableDeriveDifferent (0 ms)
[ RUN      ] SmartExpressionDerivationTest.AdditionDerive
[       OK ] SmartExpressionDerivationTest.AdditionDerive (0 ms)
[ RUN      ] SmartExpressionDerivationTest.MultiplicationDerive
[       OK ] SmartExpressionDerivationTest.MultiplicationDerive (0 ms)
[----------] 5 tests from SmartExpressionDerivationTest (1 ms total)

[----------] 3 tests from SmartExpressionSimplifyTest
[ RUN      ] SmartExpressionSimplifyTest.SimplifyAddition
[       OK ] SmartExpressionSimplifyTest.SimplifyAddition (0 ms)
[ RUN      ] SmartExpressionSimplifyTest.SimplifyMultiplication
[       OK ] SmartExpressionSimplifyTest.SimplifyMultiplication (0 ms)
[ RUN      ] SmartExpressionSimplifyTest.SimplifyComplexExpression
[       OK ] SmartExpressionSimplifyTest.SimplifyComplexExpression (0 ms)
[----------] 3 tests from SmartExpressionSimplifyTest (1 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 3 test suites ran. (6 ms total)
[  PASSED  ] 12 tests.
Nbr instances créées: 43
Nbr instances détruites: 43*/

/* On remarque qu'actuellement notre code créait de nouvelles instances inutlement dans les méthodes simplify de nombre et variable!
Pour pallier cette utilisaiton non nécessaire nous allons utiliser shared_from_this() permettant de retourner un pointeur vers l'instance existante.
La classe mère va donc hériter de std::enable_shared_from_this<SmartExpression> pour utiliser la méthode souhaiter!
On remarque que le nombres d'instances créées a bien diminué, permettant d'avoir une verison simplifiée.

~/workspace/3if1020/tp/clp_tp3: ./TestSmartExpression
[==========] Running 12 tests from 3 test suites.
[----------] Global test environment set-up.
[----------] 4 tests from SmartExpressionDisplayTest
[ RUN      ] SmartExpressionDisplayTest.NombreDisplay
[       OK ] SmartExpressionDisplayTest.NombreDisplay (0 ms)
[ RUN      ] SmartExpressionDisplayTest.VariableDisplay
[       OK ] SmartExpressionDisplayTest.VariableDisplay (0 ms)
[ RUN      ] SmartExpressionDisplayTest.AdditionDisplay
[       OK ] SmartExpressionDisplayTest.AdditionDisplay (0 ms)
[ RUN      ] SmartExpressionDisplayTest.MultiplicationDisplay
[       OK ] SmartExpressionDisplayTest.MultiplicationDisplay (0 ms)
[----------] 4 tests from SmartExpressionDisplayTest (0 ms total)

[----------] 5 tests from SmartExpressionDerivationTest
[ RUN      ] SmartExpressionDerivationTest.NombreDerive
[       OK ] SmartExpressionDerivationTest.NombreDerive (0 ms)
[ RUN      ] SmartExpressionDerivationTest.VariableDeriveSame
[       OK ] SmartExpressionDerivationTest.VariableDeriveSame (0 ms)
[ RUN      ] SmartExpressionDerivationTest.VariableDeriveDifferent
[       OK ] SmartExpressionDerivationTest.VariableDeriveDifferent (0 ms)
[ RUN      ] SmartExpressionDerivationTest.AdditionDerive
[       OK ] SmartExpressionDerivationTest.AdditionDerive (0 ms)
[ RUN      ] SmartExpressionDerivationTest.MultiplicationDerive
[       OK ] SmartExpressionDerivationTest.MultiplicationDerive (0 ms)
[----------] 5 tests from SmartExpressionDerivationTest (0 ms total)

[----------] 3 tests from SmartExpressionSimplifyTest
[ RUN      ] SmartExpressionSimplifyTest.SimplifyAddition
[       OK ] SmartExpressionSimplifyTest.SimplifyAddition (0 ms)
[ RUN      ] SmartExpressionSimplifyTest.SimplifyMultiplication
[       OK ] SmartExpressionSimplifyTest.SimplifyMultiplication (0 ms)
[ RUN      ] SmartExpressionSimplifyTest.SimplifyComplexExpression
[       OK ] SmartExpressionSimplifyTest.SimplifyComplexExpression (0 ms)
[----------] 3 tests from SmartExpressionSimplifyTest (0 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 3 test suites ran. (0 ms total)
[  PASSED  ] 12 tests.
Nbr instances créées: 36
Nbr instances détruites: 36
*/