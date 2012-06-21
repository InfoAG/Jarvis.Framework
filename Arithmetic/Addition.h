#ifndef ADDITION_H
#define ADDITION_H

#include "AbstractBinaryOperation.h"

namespace CAS {

class Addition : public AbstractBinaryOperation
{
public:
    inline Addition(AbstractArithmetic *first_op, AbstractArithmetic *second_op) : AbstractBinaryOperation(first_op, second_op) {};
    virtual inline AbstractArithmetic *copy() const { return new Addition(*this); };

    virtual AbstractArithmetic *eval(const EvalInfo &ei) const;
    virtual inline ArithmeticType getType() const { return ADDITION; };
};

}

#endif ADDITION_H
