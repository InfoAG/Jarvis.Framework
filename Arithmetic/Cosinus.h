#ifndef COSINUS_H
#define COSINUS_H

#include "AbstractArithmetic.h"

namespace CAS {

class Cosinus : public AbstractUnaryOperation
{
public:
    inline Cosinus(AbstractArithmetic *operand) : AbstractUnaryOperation(operand) {};
    virtual inline AbstractArithmetic *copy() const { return new Cosinus(*this); };

    virtual inline AbstractArithmetic *eval(const EvalInfo &ei) const { return this->copy(); };
    virtual inline ArithmeticType getType() const { return COSINUS; };
};

}

#endif //COSINUS_H
