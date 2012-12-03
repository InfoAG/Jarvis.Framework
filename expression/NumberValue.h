#ifndef NUMBERARITH_H
#define NUMBERARITH_H

#include "AbstractExpression.h"
#include <sstream>
#include <math.h>

namespace CAS {

class List;
class VectorExpression;

class NumberValue : public AbstractExpression
{
private:
    double value;

public:
    NumberValue(double value) : value(std::move(value)) {};
    virtual ExpressionP copy() const { return make_unique<NumberValue>(*this); }

    virtual ExpressionP eval(Scope &, const std::function<void(const std::string &)> &, bool, bool) const { return copy(); }
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &) { if (candidates.contains(TypeInfo::NUMBER)) return TypeInfo::NUMBER;  else throw "typing"; }
    virtual std::string toString() const { std::ostringstream ss; ss << value; return ss.str(); }
    virtual bool equals(const AbstractExpression *other) const;
    virtual bool isValue() const { return true; }

    double getValue() const { return value; }
    //double &getValue() { return value; }

    NumberValue operator+(const NumberValue &other) { return NumberValue(value + other.value); }
    NumberValue operator-(const NumberValue &other) { return NumberValue(value - other.value); }
    NumberValue operator/(const NumberValue &other) { return NumberValue(value / other.value); }
    NumberValue operator*(const NumberValue &other) { return NumberValue(value * other.value); }
    NumberValue operator%(const NumberValue &other) { return NumberValue(std::fmod(value, other.value)); }

    List operator/(const List &other);
    VectorExpression operator/(const VectorExpression &other);
};

inline NumberValue pow(const NumberValue &first, const NumberValue &second) { double res = 1; for (double exp = second.getValue(); exp != 0;exp--) res *= first.getValue(); return res; }

}

#endif //NUMBERARITH_H
