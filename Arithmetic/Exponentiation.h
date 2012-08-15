#ifndef EXPONENTIATION_H
#define EXPONENTIATION_H

#include "AbstractBinaryOperation.h"

namespace CAS {

class Exponentiation : public AbstractBinaryOperation
{
public:
    Exponentiation(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return std::unique_ptr<AbstractArithmetic>(new Exponentiation(*this)); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const { return this->copy(); }
    virtual ArithmeticType getType() const { return EXPONENTIATION; }
};

}

#endif //EXPONENTIATION_H
