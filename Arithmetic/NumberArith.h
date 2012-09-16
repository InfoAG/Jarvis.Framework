#ifndef NUMBERARITH_H
#define NUMBERARITH_H

#include "AbstractArithmetic.h"
#include "Natural.h"
#include <sstream>

namespace CAS {

class NumberArith : public AbstractArithmetic
{
private:
    Natural value; //change to CAS::Integer etc.

public:
    NumberArith(const Natural &value) : value(value) {};
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<NumberArith>(*this); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &) const { return copy(); }
    virtual ArithmeticType type() const { return NUMBERARITH; }
    virtual std::string toString() const { return value.toString(); }
    virtual bool equals(const AbstractArithmetic *other) const;
    const Natural &getValue() const { return value; }
    Natural &getValue() { return value; }

    NumberArith operator+(const NumberArith &other) { return NumberArith(value + other.value); }
    NumberArith operator-(const NumberArith &other) { return NumberArith(value - other.value); }
    NumberArith operator/(const NumberArith &other) { return NumberArith(value / other.value); }
    NumberArith operator*(const NumberArith &other) { return NumberArith(value * other.value); }
    NumberArith operator%(const NumberArith &other) { return NumberArith(value % other.value); }
};

inline NumberArith pow(const NumberArith &first, const NumberArith &second) { Natural res = 1; for (Natural exp = second.getValue(); exp != 0;exp--) res *= first.getValue(); return res; }

}

#endif //NUMBERARITH_H
