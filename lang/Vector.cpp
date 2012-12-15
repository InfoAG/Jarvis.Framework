#include "Vector.h"
#include "Division.h"

namespace CAS {

inline AbstractExpression::ExpressionP Vector::executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    return make_unique<Vector>(x->executeExpression(scope, load, print, execOption), y->executeExpression(scope, load, print, execOption), z->executeExpression(scope, load, print, execOption));
}

TypeInfo Vector::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::VECTOR);
    x->typeCheck({{TypeInfo::NUMBER}}, scope);
    y->typeCheck({{TypeInfo::NUMBER}}, scope);
    z->typeCheck({{TypeInfo::NUMBER}}, scope);
    return TypeInfo::VECTOR;
}

bool Vector::isNull() const
{
    return typeid(*x) == typeid(NumberValue) && typeid(*y) == typeid(NumberValue) && typeid(*z) == typeid(NumberValue)
            && static_cast<const NumberValue*>(x.get())->getValue() == 0
            && static_cast<const NumberValue*>(y.get())->getValue() == 0
            && static_cast<const NumberValue*>(z.get())->getValue() == 0;
}

bool Vector::isUnit() const
{
    return typeid(*x) == typeid(NumberValue) && typeid(*y) == typeid(NumberValue) && typeid(*z) == typeid(NumberValue)
            && static_cast<const NumberValue*>(x.get())->getValue() == 1
            && static_cast<const NumberValue*>(y.get())->getValue() == 1
            && static_cast<const NumberValue*>(z.get())->getValue() == 1;
}

Vector &Vector::operator=(const Vector &other)
{
    if (other.x == nullptr) x = nullptr;
    else x = other.x->copyEx();
    if (other.y == nullptr) x = nullptr;
    else y = other.y->copyEx();
    if (other.z == nullptr) z = nullptr;
    else z = other.z->copyEx();
    return *this;
}

Vector Vector::operator/(const Vector &other)
{
    return Vector(make_unique<Division>(x->copyEx(), other.getX()->copyEx()), make_unique<Division>(y->copyEx(), other.getY()->copyEx()), make_unique<Division>(z->copyEx(), other.getZ()->copyEx()));
}

Vector Vector::operator/(const NumberValue &other)
{
    return Vector(make_unique<Division>(x->copyEx(), ExpressionP(static_cast<AbstractExpression*>(other.copy().get()))), make_unique<Division>(y->copyEx(), ExpressionP(static_cast<AbstractExpression*>(other.copy().get()))), make_unique<Division>(z->copyEx(), ExpressionP(static_cast<AbstractExpression*>(other.copy().get()))));
}

}
