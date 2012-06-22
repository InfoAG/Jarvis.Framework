#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "AbstractBinaryOperation.h"

namespace CAS {

class Multiplication : public AbstractBinaryOperation
{
public:
    inline Multiplication(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {};
    virtual inline std::unique_ptr<AbstractArithmetic> copy() const { return std::unique_ptr<AbstractArithmetic>(new Multiplication(*this)); };

    virtual inline std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const { return this->copy(); };
    virtual inline ArithmeticType getType() const { return MULTIPLICATION; };
};

}

#endif MULTIPLICATION_H
