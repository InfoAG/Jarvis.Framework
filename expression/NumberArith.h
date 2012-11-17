#ifndef NUMBERARITH_H
#define NUMBERARITH_H

#include "AbstractExpression.h"
#include <sstream>
#include <math.h>

namespace CAS {

class NumberArith : public AbstractExpression
{
private:
    double value;

public:
    NumberArith(double value) : value(std::move(value)) {};
    virtual ExpressionP copy() const { return make_unique<NumberArith>(*this); }

    virtual EvalRes eval(Scope &, const std::function<void(const std::string &)> &, bool, bool) const { return std::make_pair(TypeInfo{TypeInfo::NUMBER}, copy()); }
    virtual std::string toString() const { std::ostringstream ss; ss << value; return ss.str(); }
    virtual bool equals(const AbstractExpression *other) const;
    virtual bool isValue() const { return true; }

    const double &getValue() const { return value; }
    double &getValue() { return value; }

    NumberArith operator+(const NumberArith &other) { return NumberArith(value + other.value); }
    NumberArith operator-(const NumberArith &other) { return NumberArith(value - other.value); }
    NumberArith operator/(const NumberArith &other) { return NumberArith(value / other.value); }
    NumberArith operator*(const NumberArith &other) { return NumberArith(value * other.value); }
    NumberArith operator%(const NumberArith &other) { return NumberArith(std::fmod(value, other.value)); }
};

inline NumberArith pow(const NumberArith &first, const NumberArith &second) { double res = 1; for (double exp = second.getValue(); exp != 0;exp--) res *= first.getValue(); return res; }

}

#endif //NUMBERARITH_H
