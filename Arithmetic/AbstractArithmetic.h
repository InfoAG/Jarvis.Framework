#ifndef ABSTRACTARITHMETIC_H
#define ABSTRACTARITHMETIC_H

#include "EvalInfo.h"

namespace CAS {

class AbstractArithmetic
{
public:
    virtual inline ~AbstractArithmetic() {};
    virtual AbstractArithmetic *copy() const = 0;

    virtual AbstractArithmetic *eval(const EvalInfo &ei) const = 0;
};

}

#endif //ABSTRACTARITHMETIC_H
