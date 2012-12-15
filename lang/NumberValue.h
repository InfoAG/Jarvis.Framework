#ifndef NUMBERARITH_H
#define NUMBERARITH_H

#include "AbstractExpression.h"
#include <sstream>
#include <math.h>

namespace CAS {

class List;
class Vector;

class NumberValue : public AbstractExpression
{
private:
    double value;

public:
    NumberValue(double value) : value(std::move(value)) {}
    virtual StatementP copy() const { return make_unique<NumberValue>(*this); }

    virtual ExpressionP executeExpression(Scope &, const LoadFunc &, const PrintFunc &, ExecOption) const { return copyEx(); }
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &) { candidates.assertContains(*this, TypeInfo::NUMBER); return TypeInfo::NUMBER; }
    virtual ExpressionP substituteConstants() const { return copyEx(); }
    virtual ExpressionP differentiate(const std::string &) const { return make_unique<NumberValue>(0); }
    virtual std::string toString() const { std::ostringstream ss; ss << value; return ss.str(); }
    virtual bool equals(const AbstractStatement *other) const;
    virtual bool isValue() const { return true; }
    virtual bool hasVar(const std::string &) const { return false; }
    virtual bool isSymbolic(Scope &) const { return false; }

    double getValue() const { return value; }
    //double &getValue() { return value; }

    NumberValue operator+(const NumberValue &other) { return NumberValue(value + other.value); }
    NumberValue operator-(const NumberValue &other) { return NumberValue(value - other.value); }
    NumberValue operator/(const NumberValue &other) { return NumberValue(value / other.value); }
    NumberValue operator*(const NumberValue &other) { return NumberValue(value * other.value); }
    NumberValue operator%(const NumberValue &other) { return NumberValue(std::fmod(value, other.value)); }

    List operator/(const List &other);
    Vector operator/(const Vector &other);
};

}

#endif //NUMBERARITH_H
