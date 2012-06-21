#ifndef DIVISION_H
#define DIVISION_H

#include "AbstractBinaryOperation.h"

namespace CAS {

class Division : public AbstractBinaryOperation
{
public:
    inline Division(AbstractArithmetic *first_op, AbstractArithmetic *second_op) : AbstractBinaryOperation(first_op, second_op) {};
    virtual inline AbstractArithmetic *copy() const { return new Division(*this); };

    virtual inline AbstractArithmetic *eval(const EvalInfo &ei) const { return this->copy(); };
    virtual inline ArithmeticType getType() const { return DIVISION; };
};

}

#endif DIVISION_H
