#ifndef SINUS_H
#define SINUS_H

#include "AbstractUnaryOperation.h"

namespace CAS {

class Sinus : public AbstractUnaryOperation
{
public:
    virtual inline AbstractArithmetic *copy() const { return new Addition(*this); };

    virtual inline AbstractArithmetic *eval(const EvalInfo &ei) const { return this->copy(); };
};

}

#endif ADDITION_H
