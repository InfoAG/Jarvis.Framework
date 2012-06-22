#ifndef DIVISION_H
#define DIVISION_H

#include "AbstractBinaryOperation.h"

namespace CAS {

class Division : public AbstractBinaryOperation
{
public:
    inline Division(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {};
    virtual inline std::unique_ptr<AbstractArithmetic> copy() const { return std::unique_ptr<AbstractArithmetic>(new Division(*this)); };

    virtual inline std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const { return this->copy(); };
    virtual inline ArithmeticType getType() const { return DIVISION; };
};

}

#endif DIVISION_H
