#ifndef NUMBERARITH_H
#define NUMBERARITH_H

#include "AbstractExpression.h"
#include "Integer.h"
#include <sstream>

namespace CAS {

class NumberArith : public AbstractExpression
{
private:
    Integer value;

public:
    NumberArith(const Integer &value) : value(value) {};
    virtual ExpressionP copy() const { return make_unique<NumberArith>(*this); }

    virtual EvalRes eval(Scope &, const std::function<void(const std::string &)> &, bool, bool) const { return std::make_pair(TypeInfo{TypeInfo::NUMBER}, copy()); }
    virtual std::string toString() const { return value.toString(); }
    virtual bool equals(const AbstractExpression *other) const;
    virtual bool isValue() const { return true; }

    const Integer &getValue() const { return value; }
    Integer &getValue() { return value; }

    NumberArith operator+(const NumberArith &other) { return NumberArith(value + other.value); }
    NumberArith operator-(const NumberArith &other) { return NumberArith(value - other.value); }
    NumberArith operator/(const NumberArith &other) { return NumberArith(value / other.value); }
    NumberArith operator*(const NumberArith &other) { return NumberArith(value * other.value); }
    NumberArith operator%(const NumberArith &other) { return NumberArith(value % other.value); }
};

inline NumberArith pow(const NumberArith &first, const NumberArith &second) { Integer res = 1; for (Integer exp = second.getValue(); exp != 0;exp--) res *= first.getValue(); return res; }

}

#endif //NUMBERARITH_H
