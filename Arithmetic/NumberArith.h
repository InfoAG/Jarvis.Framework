#ifndef NUMBERARITH_H
#define NUMBERARITH_H

#include "AbstractArithmetic.h"
#include <sstream>

namespace CAS {

class NumberArith : public AbstractArithmetic
{
private:
    double value; //change to CAS::Integer etc.

public:
    NumberArith(double value) : value(value) {};
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<NumberArith>(*this); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const { return copy(); }
    virtual ArithmeticType type() const { return NUMBERARITH; }
    virtual std::string toString() const;
    virtual inline bool equals(const AbstractArithmetic *other) const;
    double getValue() const { return value; }

    NumberArith operator+(const NumberArith& other) { return NumberArith(value + other.value); }
    NumberArith operator-(const NumberArith& other) { return NumberArith(value - other.value); }
    NumberArith operator/(const NumberArith& other) { return NumberArith(value / other.value); }
    NumberArith operator*(const NumberArith& other) { return NumberArith(value * other.value); }
};

inline NumberArith pow(const NumberArith &first, const NumberArith &second) { return std::pow(first.getValue(), second.getValue()); }

}

#endif //NUMBERARITH_H
