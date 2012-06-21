#ifndef EXPONENTIATION_H
#define EXPONENTIATION_H

#include "AbstractBinaryOperation.h"

namespace CAS {

class Exponentiation : public AbstractBinaryOperation
{
public:
    Exponentiation(AbstractArithmetic *first_op, AbstractArithmetic *second_op) : AbstractBinaryOperation(first_op, second_op) {};
    virtual inline AbstractArithmetic *copy() const { return new Exponentiation(*this); };

    virtual inline AbstractArithmetic *eval(const EvalInfo &ei) const { return this->copy(); };
    virtual inline ArithmeticType getType() const { return EXPONENTIATION; };
};

}

#endif EXPONENTIATION_H
