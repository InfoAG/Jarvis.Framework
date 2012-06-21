#ifndef SINUS_H
#define SINUS_H

#include "AbstractUnaryOperation.h"

namespace CAS {

class Sinus : public AbstractUnaryOperation
{
public:
    inline Sinus(AbstractArithmetic *operand) : AbstractUnaryOperation(operand) {};
    virtual inline AbstractArithmetic *copy() const { return new Sinus(*this); };

    virtual inline AbstractArithmetic *eval(const EvalInfo &ei) const { return this->copy(); };
    virtual inline ArithmeticType getType() const { return SINUS; };
};

}

#endif ADDITION_H
