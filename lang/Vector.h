#ifndef VECTOR_H
#define VECTOR_H

#include "AbstractExpression.h"
#include "NumberValue.h"

namespace CAS {

class Vector : public AbstractExpression
{
private:
    ExpressionP x, y, z;

public:
    static Vector null() { return Vector(make_unique<NumberValue>(0), make_unique<NumberValue>(0), make_unique<NumberValue>(0)); }
    static Vector unit() { return Vector(make_unique<NumberValue>(1), make_unique<NumberValue>(1), make_unique<NumberValue>(1)); }

    Vector() {}
    Vector(ExpressionP x, ExpressionP y, ExpressionP z) : x(std::move(x)), y(std::move(y)), z(std::move(z)) {}
    Vector(const Vector &other) : x(other.x->copyEx()), y(other.y->copyEx()), z(other.z->copyEx()) {}
    virtual StatementP copy() const { return make_unique<Vector>(*this); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &, ExecOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual ExpressionP substituteConstants() const { return make_unique<Vector>(x->substituteConstants(), y->substituteConstants(), z->substituteConstants()); }
    virtual bool equals(const AbstractStatement *other) const { return typeid(*other) == typeid(Vector) && *this == *static_cast<const Vector*>(other); }
    virtual std::string toString() const { return "(" + x->toString() + "," + y->toString() + "," + z->toString() + ")"; }
    virtual bool isValue() const { return true; }
    virtual bool isSymbolic(Scope &scope) const { return x->isSymbolic(scope) || y->isSymbolic(scope) || z->isSymbolic(scope); }

    bool isNull() const;
    bool isUnit() const;
    ExpressionP &getX() { return x; }
    ExpressionP &getY() { return y; }
    ExpressionP &getZ() { return z; }
    const ExpressionP &getX() const { return x; }
    const ExpressionP &getY() const { return y; }
    const ExpressionP &getZ() const { return z; }

    Vector &operator=(const Vector &other);

    Vector operator/(const Vector &other);
    Vector operator/(const NumberValue &other);

    bool operator==(const Vector &other) const { return x->equals(other.x.get()) && y->equals(other.y.get()) && z->equals(other.z.get()); }
};

}

#endif // VECTOR_H
