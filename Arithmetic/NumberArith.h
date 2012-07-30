#ifndef NUMBERARITH_H
#define NUMBERARITH_H

#include "AbstractArithmetic.h"
#include <sstream>

namespace CAS {

class NumberArith : public AbstractArithmetic
{
private:
    int value; //change to CAS::Integer etc.

public:
    inline NumberArith(int value) : value(value) {};
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return std::unique_ptr<AbstractArithmetic>(new NumberArith(*this)); };

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const { return copy(); };
    virtual ArithmeticType getType() const { return NUMBERARITH; };
    virtual std::string getString() const;

    inline NumberArith operator+(const NumberArith& other) { return NumberArith(value + other.value); };
    inline NumberArith operator/(const NumberArith& other) { return NumberArith(value / other.value); };
    inline NumberArith operator*(const NumberArith& other) { return NumberArith(value * other.value); };
};

}

#endif //NUMBERARITH_H
