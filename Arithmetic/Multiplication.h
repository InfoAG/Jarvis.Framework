#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "AbstractBinaryOperation.h"

namespace CAS {

class Multiplication : public AbstractBinaryOperation
{
public:
    inline Multiplication(AbstractArithmetic *first_op, AbstractArithmetic *second_op) : AbstractBinaryOperation(first_op, second_op) {};
    virtual inline AbstractArithmetic *copy() const { return new Multiplication(*this); };

    virtual inline AbstractArithmetic *eval(const EvalInfo &ei) const { return this->copy(); };
    virtual inline ArithmeticType getType() const { return MULTIPLICATION; };
};

}

#endif MULTIPLICATION_H
