/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * SmartExpression.hpp
 */

#ifndef SMART_EXPRESSION_HPP_INCLUDED
#define SMART_EXPRESSION_HPP_INCLUDED

#include <iostream>
#include <string>
#include <utility>
#include <memory>

class SmartNombre;

class SmartExpression : public std::enable_shared_from_this<SmartExpression> {
public:
    virtual ~SmartExpression();

    //Méthodes pour obtenir les compteurs d'instances
    static int getInstanceCount() { return count_created; }
    static int getDestroyedCount() { return count_destroyed; }

    // Méthodes virtuelles pures
    virtual std::shared_ptr<SmartExpression> simplify() const = 0;
    virtual std::shared_ptr<SmartExpression> derive(const std::string& variable_name) const = 0;
    virtual float compute() const = 0;

    //Affichage
    friend std::ostream& operator<<(std::ostream& os, const SmartExpression& expr) {
        expr.print(os);
        return os;
    }

    //Instances statiques pour 0 et 1 afin d'éviter de les recréer dans les dérivations
    static std::shared_ptr<SmartNombre> zero;
    static std::shared_ptr<SmartNombre> one;

protected:
    SmartExpression();
    virtual void print(std::ostream& os) const = 0;
    static int count_created;
    static int count_destroyed;
};

class SmartNombre : public SmartExpression {
public:
    explicit SmartNombre(float value);
    SmartNombre(const SmartNombre& other);
    std::shared_ptr<SmartExpression> simplify() const override;
    std::shared_ptr<SmartExpression> derive(const std::string& variable_name) const override;
    float compute() const override;

protected:
    void print(std::ostream& os) const override;

private:
    float value_;
};

class SmartVariable : public SmartExpression {
public:
    explicit SmartVariable(const std::string& name);
    SmartVariable(const SmartVariable& other);
    std::shared_ptr<SmartExpression> simplify() const override;
    std::shared_ptr<SmartExpression> derive(const std::string& variable_name) const override;
    float compute() const override;

protected:
    void print(std::ostream& os) const override;

private:
    std::string name_;
};

class SmartOperation : public SmartExpression {
public:
    SmartOperation(std::shared_ptr<SmartExpression> left, std::shared_ptr<SmartExpression> right);
    SmartOperation(const SmartOperation& other);
protected:
    std::shared_ptr<SmartExpression> left_operand_;
    std::shared_ptr<SmartExpression> right_operand_;
};

class SmartAddition : public SmartOperation {
public:
    using SmartOperation::SmartOperation;

    std::shared_ptr<SmartExpression> simplify() const override;
    std::shared_ptr<SmartExpression> derive(const std::string& variable_name) const override;
    float compute() const override;

protected:
    void print(std::ostream& os) const override;
};

class SmartMultiplication : public SmartOperation {
public:
    using SmartOperation::SmartOperation;

    std::shared_ptr<SmartExpression> simplify() const override;
    std::shared_ptr<SmartExpression> derive(const std::string& variable_name) const override;
    float compute() const override;

protected:
    void print(std::ostream& os) const override;
};

#endif
