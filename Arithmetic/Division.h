#ifndef DIVISION_H
#define DIVISION_H

#include "AbstractBinaryOperation.h"
#include "NumberArith.h"

namespace CAS {

class Division : public AbstractBinaryOperation
{
public:
    Division(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<Division>(*this); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType type() const { return DIVISION; }
    virtual std::string toString() const;
    virtual bool equals(const AbstractArithmetic *other) const;
};

}

#endif //DIVISION_H
