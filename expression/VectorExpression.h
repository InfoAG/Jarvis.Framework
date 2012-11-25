#ifndef VECTOREXPRESSION_H
#define VECTOREXPRESSION_H

#include "AbstractExpression.h"
#include "NumberArith.h"

namespace CAS {

class VectorExpression : public AbstractExpression
{
private:
    ExpressionP x, y, z;

public:
    static VectorExpression null() { return VectorExpression(make_unique<NumberArith>(0), make_unique<NumberArith>(0), make_unique<NumberArith>(0)); }
    static VectorExpression unit() { return VectorExpression(make_unique<NumberArith>(1), make_unique<NumberArith>(1), make_unique<NumberArith>(1)); }

    VectorExpression() {}
    VectorExpression(ExpressionP x, ExpressionP y, ExpressionP z) : x(std::move(x)), y(std::move(y)), z(std::move(z)) {}
    VectorExpression(const VectorExpression &other) : x(other.x->copy()), y(other.y->copy()), z(other.z->copy()) {}
    virtual ExpressionP copy() const { return make_unique<VectorExpression>(*this); }

    virtual EvalRes eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
    virtual bool equals(const AbstractExpression *other) const { return typeid(*other) == typeid(VectorExpression) && *this == *static_cast<const VectorExpression*>(other); }
    virtual std::string toString() const { return "(" + x->toString() + "," + y->toString() + "," + z->toString() + ")"; }
    virtual bool isValue() const { return true; }

    bool isNull() const;
    bool isUnit() const;
    ExpressionP &getX() { return x; }
    ExpressionP &getY() { return y; }
    ExpressionP &getZ() { return z; }
    const ExpressionP &getX() const { return x; }
    const ExpressionP &getY() const { return y; }
    const ExpressionP &getZ() const { return z; }

    VectorExpression &operator=(const VectorExpression &other);

    bool operator==(const VectorExpression &other) const { return x->equals(other.x.get()) && y->equals(other.y.get()) && z->equals(other.z.get()); }
};

}

#endif // VECTOREXPRESSION_H
