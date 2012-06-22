#ifndef ABSTRACTARITHMETIC_H
#define ABSTRACTARITHMETIC_H

#include "EvalInfo.h"
#include <memory>

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
        NUMBERARITH,
        VARIABLE
    };

    virtual inline ~AbstractArithmetic() {};
    virtual std::unique_ptr<AbstractArithmetic> copy() const = 0;

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const = 0;
    virtual ArithmeticType getType() const = 0;
};

}

#endif //ABSTRACTARITHMETIC_H
