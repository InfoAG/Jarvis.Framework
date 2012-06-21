#ifndef ABSTRACTARITHMETIC_H
#define ABSTRACTARITHMETIC_H

#include "EvalInfo.h"

namespace CAS {

class AbstractArithmetic
{
public:
    enum ArithmeticType {
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION,
        EXPONENTIATION,
        ROOT,
        LOGARITHM,
        SINUS,
        COSINUS,
        TANGENT,
        INTEGRAL,
        NUMBER,
        VARIABLE
    };

    virtual inline ~AbstractArithmetic() {};
    virtual AbstractArithmetic *copy() const = 0;

    virtual AbstractArithmetic *eval(const EvalInfo &ei) const = 0;
    virtual ArithmeticType getType() const = 0;
};

}

#endif //ABSTRACTARITHMETIC_H
