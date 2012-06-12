#ifndef ADDITION_H
#define ADDITION_H

#include "AbstractBinaryOperation.h"

namespace CAS {

class Addition : public AbstractBinaryOperation
{
public:
    virtual inline AbstractArithmetic *copy() const { return new Addition(*this); };

    virtual inline AbstractArithmetic *eval(const EvalInfo &ei) const { return this->copy(); };
};

}

#endif ADDITION_H
