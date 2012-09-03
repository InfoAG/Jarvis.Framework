#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "AbstractBinaryOperation.h"
#include "NumberArith.h"
#include "Addition.h"

namespace CAS {

class Subtraction : public AbstractBinaryOperation
{
public:
    Subtraction(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<Subtraction>(*this); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType type() const { return SUBTRACTION; }
    virtual std::string toString() const { return first_op->toString() + "-" + second_op->toString(); }
    virtual bool equals(const AbstractArithmetic *other) const;
};

}

#endif //SUBTRACTION_H
