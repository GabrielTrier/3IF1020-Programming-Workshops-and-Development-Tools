/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * Expression.hpp
 */

#ifndef EXPRESSION_HPP_INCLUDED
#define EXPRESSION_HPP_INCLUDED

#include <iostream>
#include <string>
#include <iomanip> 


class Expression {
public:
    virtual ~Expression() {++count_destroyed;};

    // Constructeurs et opérateurs de copie par défaut
    Expression(const Expression&) = default;
    Expression& operator=(const Expression&) = default;

    // Surcharge de l'opérateur << pour l'affichage
    friend std::ostream& operator<<(std::ostream& os, const Expression& expr) {
        expr.print(os);
        return os;
    }

    /**
     * Calcule la dérivée de l'expression par rapport à une variable.
     *
     * Cette méthode crée et retourne une nouvelle instance représentant la dérivée
     * de l'expression actuelle par rapport à la variable spécifiée. L'instance courante
     * n'est pas modifiée.
     *
     * @param variable_name Le nom de la variable par rapport à laquelle dériver.
     * @return Expression* Un pointeur vers une nouvelle instance représentant la dérivée.
     * L'appelant est responsable de libérer la mémoire allouée.
     */
    virtual Expression* derive(const std::string& variable_name) const = 0;
    
    virtual float compute() const = 0;
    virtual Expression* clone() const  = 0;

    /** Explication: 
     * Pour la partie 1.4, l'objectif est de simplifier l'expression au maximum lorsque cela est possible.
     * Aucune simplification ne peut etre faite concernant les Nombres et Variables a priori. 
     * Nous avons identifié 5 cas de figures de simplification du code actuel, notamment concernant les Additions et Multiplications: 
     * Addition: 
     * - Si les deux opérandes sont des Nombres, calculer la somme et retourner un Nombre.
     * - Si l'un des opérandes est 0, retourner l'autre opérande.
     * Multiplication:
     * - Si les deux opérandes sont des Nombres, calculer le produit et retourner un Nombre.
     * - Si l'un des opérandes est 1, retourner l'autre opérande.
     * - Si l'un des opérandes est 0, retourner un Nombre 0.
     * 
     * @brief Pour réaliser cela nous implémentons la méthode simplify(), qui crée et retourne une nouvelle instance représentant la version simplifiée de l'expression courante. 
     * Si l'expression ne peut pas être simplifiée davantage, elle peut retourner une copie de l'expression courante.
     * @return Expression* , pointeur vers une nouvelle expression simplifiée.
     */
    virtual Expression* simplify() const = 0;

    //Compteur nbr instances créées et détruites
    static int getInstanceCount() {return count_created;}
    static int getDestroyedCount() {return count_destroyed;}
protected:
    Expression() {++count_created;}; 
    virtual void print(std::ostream& os) const = 0;
private:
    static int count_created;   
    static int count_destroyed;  
};

class Nombre : public Expression {
public:
    explicit Nombre(float value) : value_(value) {}

    Nombre(const Nombre& other) : value_(other.value_) {}

    Nombre& operator=(const Nombre& other) {
        if (this != &other) { value_ = other.value_; }
        return *this;
    }

    ~Nombre() override = default;

    //Méthode simplify 
    Expression* simplify() const override {return new Nombre(*this);}

    // Dérivée d'un nombre constante
    Expression* derive(const std::string& variable_name) const override {
        return new Nombre(0.0);
    }

    float compute() const override {
    return value_;
    }
    //Nécessité d'implémenter la fonction dans les classes dérivées sinon abstraites
    Expression* clone() const override {
        return new Nombre(*this);
    }
protected:
    void print(std::ostream& os) const override {
        os << std::fixed << std::setprecision(1) << value_;
    }

private:
    float value_;
};

class Variable : public Expression {
public:
    explicit Variable(const std::string& name) : name_(name) {}

    Variable(const Variable& other) : name_(other.name_) {}

    Variable& operator=(const Variable& other) {
        if (this != &other) { name_ = other.name_; }
        return *this;
    }

    ~Variable() override = default;

    //Méthode simplify 
    Expression* simplify() const override {return new Variable(*this);}

    //Dérivée d'une variable par rapport à elle-même
    Expression* derive(const std::string& variable_name) const override {
        if (name_ == variable_name) {
            return new Nombre(1.0);
        } else {
            return new Nombre(0.0);
        }
    }
    float compute() const override {
    throw std::runtime_error("Pas de valeur entréé!");
    }
    //Même justification que pour nombre
    Expression* clone() const override {
        return new Variable(*this);
    } 

protected:
    void print(std::ostream& os) const override {
        os << name_;
    }

private:
    std::string name_;
};

class Operation : public Expression {
public:
    /**
     * @brief Constructeur de la classe Operation
     * @param left Pointeur vers l'opérande gauche
     * @param right Pointeur vers l'opérande droit
     */
    Operation(Expression* left, Expression* right)
        : left_operand(left), right_operand(right) {}

    //Constructeur de copie
    Operation(const Operation& other)
        : left_operand(other.left_operand ? other.left_operand->clone() : nullptr),
          right_operand(other.right_operand ? other.right_operand->clone() : nullptr) {}

    //Opérateur d'affectation par copie
    Operation& operator=(const Operation& other) {
        if (this != &other) {
            delete left_operand;
            delete right_operand;
            left_operand = other.left_operand ? other.left_operand->clone() : nullptr;
            right_operand = other.right_operand ? other.right_operand->clone() : nullptr;
        }
        return *this;
    }
    //Destructeur
    ~Operation() override {
        delete left_operand;
        delete right_operand;
    }
    //Méthode de calcul (jusitfiant l'existance de la classe)
    float compute() const  override = 0;

    //Méthode clone opération courante
    virtual Expression* clone() const override = 0;

protected:
    void print(std::ostream& os) const override {
        os << "(";
        os << *left_operand;
        os << " ? ";
        os << *right_operand;
        os << ")";
    }
    Expression* left_operand; 
    Expression* right_operand;
};

class Addition : public Operation {
public:
    Addition(Expression* left, Expression* right)
        : Operation(left, right) {}

    float compute() const override {
        return left_operand->compute() + right_operand->compute();
    }

    Expression* derive(const std::string& variable_name) const override {
        return new Addition(left_operand->derive(variable_name),
                            right_operand->derive(variable_name));
    }
    //Même chose 
    Expression* clone() const override {
        return new Addition(left_operand->clone(), right_operand->clone());
    }
    //Méthode simplify
    Expression* simplify() const override {
        Expression* simplified_left = left_operand->simplify();
        Expression* simplified_right = right_operand->simplify();
        Nombre* left_num = dynamic_cast<Nombre*>(simplified_left);
        Nombre* right_num = dynamic_cast<Nombre*>(simplified_right);

        if (left_num && right_num) {//Calcul la somme si 2 opérandes sont des nombres 
            float sum = left_num->compute() + right_num->compute();
            delete simplified_left;
            delete simplified_right;
            return new Nombre(sum);
        }
        //Gauche = 0 , donc on retourne le droit 
        if (left_num && left_num->compute() == 0.0f) {
            delete simplified_left;
            return simplified_right;
        }
        //Cas inverse
        if (right_num && right_num->compute() == 0.0f) {
            delete simplified_right;
            return simplified_left; 
        }
        //Cas sans simplification
        return new Addition(simplified_left, simplified_right);
    }

protected:
    void print(std::ostream& os) const override {
        os << "(" << *left_operand << " + " << *right_operand << ")";
    }
};

class Multiplication : public Operation {
public:
    Multiplication(Expression* left, Expression* right)
        : Operation(left, right) {}

    float compute() const override {
        return left_operand->compute() * right_operand->compute();
    }

    Multiplication* clone() const override {
        return new Multiplication(left_operand->clone(), right_operand->clone());
    }
    
    //Méthode simplify
    Expression* simplify() const override {
        
        Expression* simplified_left = left_operand->simplify();
        Expression* simplified_right = right_operand->simplify();
        Nombre* left_num = dynamic_cast<Nombre*>(simplified_left);
        Nombre* right_num = dynamic_cast<Nombre*>(simplified_right);

        if (left_num && right_num) {//Calcul de produit
            float product = left_num->compute() * right_num->compute();
            delete simplified_left;
            delete simplified_right;
            return new Nombre(product);
        }
        //Simplification avec 0
        if ((left_num && left_num->compute() == 0.0f) || (right_num && right_num->compute() == 0.0f)) {
            delete simplified_left;
            delete simplified_right;
            return new Nombre(0.0f); //Retourne 0 directement 
        }
        //Simplification avec 1
        if (left_num && left_num->compute() == 1.0f) {
            delete simplified_left;
            return simplified_right; //Retourne droit
        }
        if (right_num && right_num->compute() == 1.0f) {
            delete simplified_right;
            return simplified_left; //Même principe mais gauche
        }
        //Cas sans simplification
        return new Multiplication(simplified_left, simplified_right);
    }

    Expression* derive(const std::string& variable_name) const override {
        return new Addition(
            new Multiplication(left_operand->derive(variable_name), right_operand->clone()),
            new Multiplication(left_operand->clone(), right_operand->derive(variable_name))
        );
    }

protected:
    void print(std::ostream& os) const override {
        os << "(" << *left_operand << " * " << *right_operand << ")";
    }
};

#endif 

/*************************Iteration 1************************************ */

/*
L'intérêt de cette super-classe Operation pour les opérations arithmétiques (addition et multiplication) 
est de regrouper des comportements communs pour les opérations futures (principe de Liskov du SOLID). 

Nous optons pour une méthode qui crée une nouvelle instance au lieu de modifier l'existante!
Cela permet de garder les objets immuables et d'éviter des effets secondaires. 
*/

/*************************Iteration 2************************************ */
/*
Nous utilisons des pointeurs bruts pour gérés les 2 opérandes (gauche et droite) qui sont des objets de type expression!
Nous définissons la méthode justifiant l'existance de la classe Operation étant : Compute .
Les opérandes sont copiées dynamiquement afin de garantir que Operation détient ses propres instances, empêchant donc les modifications et/ou destruction des objets initiaux.
Nous utilisons donc un destructeur afin de libéréer la mémmoire allouée dynamiquement.
Nous définissions une méthode print globale afin de fair eun affichage spécifique pour chaque opération ou le "?" sera remplacer par le symbole de l'opération!
*/

/*
Il est nécessaire d'introduire la méthode clone dans toute les classes (mère-filles) car dans notre cas de figure,
on dérive ou copie des opérations complexes dont le type est inconnue.
Donc pour pallier ce problème, nous utilisons clone afin de créér une copie précise.
L'ajout de cette fonction permet d'assurer une gestion dynamique des types dérivés!
*/

/*************************Simplification************************************ */

/*Echec des tests de simplification car méthodes non implémentées!

~/workspace/3if1020/tp/clp_tp3: ./TestExpression                                                                    
[==========] Running 17 tests from 3 test suites.
[----------] Global test environment set-up.
[----------] 4 tests from ExpressionDisplayTest
[ RUN      ] ExpressionDisplayTest.NombreDisplay
[       OK ] ExpressionDisplayTest.NombreDisplay (0 ms)
[ RUN      ] ExpressionDisplayTest.VariableDisplay
[       OK ] ExpressionDisplayTest.VariableDisplay (0 ms)
[ RUN      ] ExpressionDisplayTest.AdditionDisplay
[       OK ] ExpressionDisplayTest.AdditionDisplay (0 ms)
[ RUN      ] ExpressionDisplayTest.MultiplicationDisplay
[       OK ] ExpressionDisplayTest.MultiplicationDisplay (0 ms)
[----------] 4 tests from ExpressionDisplayTest (0 ms total)

[----------] 5 tests from ExpressionDerivationTest
[ RUN      ] ExpressionDerivationTest.NombreDerive
[       OK ] ExpressionDerivationTest.NombreDerive (0 ms)
[ RUN      ] ExpressionDerivationTest.VariableDeriveSame
[       OK ] ExpressionDerivationTest.VariableDeriveSame (0 ms)
[ RUN      ] ExpressionDerivationTest.VariableDeriveDifferent
[       OK ] ExpressionDerivationTest.VariableDeriveDifferent (0 ms)
[ RUN      ] ExpressionDerivationTest.AdditionDerive
[       OK ] ExpressionDerivationTest.AdditionDerive (0 ms)
[ RUN      ] ExpressionDerivationTest.MultiplicationDerive
[       OK ] ExpressionDerivationTest.MultiplicationDerive (0 ms)
[----------] 5 tests from ExpressionDerivationTest (0 ms total)

[----------] 8 tests from ExpressionSimplifyTest
[ RUN      ] ExpressionSimplifyTest.AdditionOfNumbersSimplify
TestExpression.cpp:19: Failure
Expected equality of these values:
  oss.str()
    Which is: "(3.0 + 4.0)"
  expected
    Which is: "7.0"

[  FAILED  ] ExpressionSimplifyTest.AdditionOfNumbersSimplify (0 ms)
[ RUN      ] ExpressionSimplifyTest.AdditionWithZeroLeftSimplify
TestExpression.cpp:19: Failure
Expected equality of these values:
  oss.str()
    Which is: "(0.0 + x)"
  expected
    Which is: "x"

[  FAILED  ] ExpressionSimplifyTest.AdditionWithZeroLeftSimplify (0 ms)
[ RUN      ] ExpressionSimplifyTest.AdditionWithZeroRightSimplify
TestExpression.cpp:19: Failure
Expected equality of these values:
  oss.str()
    Which is: "(x + 0.0)"
  expected
    Which is: "x"

[  FAILED  ] ExpressionSimplifyTest.AdditionWithZeroRightSimplify (0 ms)
[ RUN      ] ExpressionSimplifyTest.MultiplicationOfNumbersSimplify
TestExpression.cpp:19: Failure
Expected equality of these values:
  oss.str()
    Which is: "(3.0 * 4.0)"
  expected
    Which is: "12.0"

[  FAILED  ] ExpressionSimplifyTest.MultiplicationOfNumbersSimplify (0 ms)
[ RUN      ] ExpressionSimplifyTest.MultiplicationWithOneLeftSimplify
TestExpression.cpp:19: Failure
Expected equality of these values:
  oss.str()
    Which is: "(1.0 * x)"
  expected
    Which is: "x"

[  FAILED  ] ExpressionSimplifyTest.MultiplicationWithOneLeftSimplify (0 ms)
[ RUN      ] ExpressionSimplifyTest.MultiplicationWithOneRightSimplify
TestExpression.cpp:19: Failure
Expected equality of these values:
  oss.str()
    Which is: "(x * 1.0)"
  expected
    Which is: "x"

[  FAILED  ] ExpressionSimplifyTest.MultiplicationWithOneRightSimplify (0 ms)
[ RUN      ] ExpressionSimplifyTest.MultiplicationWithZeroLeftSimplify
TestExpression.cpp:19: Failure
Expected equality of these values:
  oss.str()
    Which is: "(0.0 * x)"
  expected
    Which is: "0.0"

[  FAILED  ] ExpressionSimplifyTest.MultiplicationWithZeroLeftSimplify (0 ms)
[ RUN      ] ExpressionSimplifyTest.MultiplicationWithZeroRightSimplify
TestExpression.cpp:19: Failure
Expected equality of these values:
  oss.str()
    Which is: "(x * 0.0)"
  expected
    Which is: "0.0"

[  FAILED  ] ExpressionSimplifyTest.MultiplicationWithZeroRightSimplify (0 ms)
[----------] 8 tests from ExpressionSimplifyTest (2 ms total)

[----------] Global test environment tear-down
[==========] 17 tests from 3 test suites ran. (3 ms total)
[  PASSED  ] 9 tests.
[  FAILED  ] 8 tests, listed below:
[  FAILED  ] ExpressionSimplifyTest.AdditionOfNumbersSimplify
[  FAILED  ] ExpressionSimplifyTest.AdditionWithZeroLeftSimplify
[  FAILED  ] ExpressionSimplifyTest.AdditionWithZeroRightSimplify
[  FAILED  ] ExpressionSimplifyTest.MultiplicationOfNumbersSimplify
[  FAILED  ] ExpressionSimplifyTest.MultiplicationWithOneLeftSimplify
[  FAILED  ] ExpressionSimplifyTest.MultiplicationWithOneRightSimplify
[  FAILED  ] ExpressionSimplifyTest.MultiplicationWithZeroLeftSimplify
[  FAILED  ] ExpressionSimplifyTest.MultiplicationWithZeroRightSimplify

 8 FAILED TESTS
*/

/* Pour pallier cela nous implémentons les méthodes Simplify dans addition et multiplication, et maintenant on peut observer la bonne réussite de tout les tests!
~/workspace/3if1020/tp/clp_tp3: ./TestExpression                                                                    
[==========] Running 17 tests from 3 test suites.
[----------] Global test environment set-up.
[----------] 4 tests from ExpressionDisplayTest
[ RUN      ] ExpressionDisplayTest.NombreDisplay
[       OK ] ExpressionDisplayTest.NombreDisplay (0 ms)
[ RUN      ] ExpressionDisplayTest.VariableDisplay
[       OK ] ExpressionDisplayTest.VariableDisplay (0 ms)
[ RUN      ] ExpressionDisplayTest.AdditionDisplay
[       OK ] ExpressionDisplayTest.AdditionDisplay (0 ms)
[ RUN      ] ExpressionDisplayTest.MultiplicationDisplay
[       OK ] ExpressionDisplayTest.MultiplicationDisplay (0 ms)
[----------] 4 tests from ExpressionDisplayTest (0 ms total)

[----------] 5 tests from ExpressionDerivationTest
[ RUN      ] ExpressionDerivationTest.NombreDerive
[       OK ] ExpressionDerivationTest.NombreDerive (0 ms)
[ RUN      ] ExpressionDerivationTest.VariableDeriveSame
[       OK ] ExpressionDerivationTest.VariableDeriveSame (0 ms)
[ RUN      ] ExpressionDerivationTest.VariableDeriveDifferent
[       OK ] ExpressionDerivationTest.VariableDeriveDifferent (0 ms)
[ RUN      ] ExpressionDerivationTest.AdditionDerive
[       OK ] ExpressionDerivationTest.AdditionDerive (0 ms)
[ RUN      ] ExpressionDerivationTest.MultiplicationDerive
[       OK ] ExpressionDerivationTest.MultiplicationDerive (0 ms)
[----------] 5 tests from ExpressionDerivationTest (0 ms total)

[----------] 8 tests from ExpressionSimplifyTest
[ RUN      ] ExpressionSimplifyTest.AdditionOfNumbersSimplify
[       OK ] ExpressionSimplifyTest.AdditionOfNumbersSimplify (0 ms)
[ RUN      ] ExpressionSimplifyTest.AdditionWithZeroLeftSimplify
[       OK ] ExpressionSimplifyTest.AdditionWithZeroLeftSimplify (0 ms)
[ RUN      ] ExpressionSimplifyTest.AdditionWithZeroRightSimplify
[       OK ] ExpressionSimplifyTest.AdditionWithZeroRightSimplify (0 ms)
[ RUN      ] ExpressionSimplifyTest.MultiplicationOfNumbersSimplify
[       OK ] ExpressionSimplifyTest.MultiplicationOfNumbersSimplify (0 ms)
[ RUN      ] ExpressionSimplifyTest.MultiplicationWithOneLeftSimplify
[       OK ] ExpressionSimplifyTest.MultiplicationWithOneLeftSimplify (0 ms)
[ RUN      ] ExpressionSimplifyTest.MultiplicationWithOneRightSimplify
[       OK ] ExpressionSimplifyTest.MultiplicationWithOneRightSimplify (0 ms)
[ RUN      ] ExpressionSimplifyTest.MultiplicationWithZeroLeftSimplify
[       OK ] ExpressionSimplifyTest.MultiplicationWithZeroLeftSimplify (0 ms)
[ RUN      ] ExpressionSimplifyTest.MultiplicationWithZeroRightSimplify
[       OK ] ExpressionSimplifyTest.MultiplicationWithZeroRightSimplify (0 ms)
[----------] 8 tests from ExpressionSimplifyTest (0 ms total)

[----------] Global test environment tear-down
[==========] 17 tests from 3 test suites ran. (1 ms total)
[  PASSED  ] 17 tests.
Nbr instances créées: 74
Nbr instances détruites: 74
*/