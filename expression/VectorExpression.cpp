#include "VectorExpression.h"
#include "Division.h"

namespace CAS {

inline AbstractExpression::ExpressionP VectorExpression::execute(Scope &scope, const std::function<void (const std::string &)> &load, ExecOption execOption) const
{
    return make_unique<VectorExpression>(x->execute(scope, load, execOption), y->execute(scope, load, execOption), z->execute(scope, load, execOption));
}

TypeInfo VectorExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::VECTOR);
    x->typeCheck({{TypeInfo::NUMBER}}, scope);
    y->typeCheck({{TypeInfo::NUMBER}}, scope);
    z->typeCheck({{TypeInfo::NUMBER}}, scope);
    return TypeInfo::VECTOR;
}

bool VectorExpression::isNull() const
{
    return typeid(*x) == typeid(NumberValue) && typeid(*y) == typeid(NumberValue) && typeid(*z) == typeid(NumberValue)
            && static_cast<const NumberValue*>(x.get())->getValue() == 0
            && static_cast<const NumberValue*>(y.get())->getValue() == 0
            && static_cast<const NumberValue*>(z.get())->getValue() == 0;
}

bool VectorExpression::isUnit() const
{
    return typeid(*x) == typeid(NumberValue) && typeid(*y) == typeid(NumberValue) && typeid(*z) == typeid(NumberValue)
            && static_cast<const NumberValue*>(x.get())->getValue() == 1
            && static_cast<const NumberValue*>(y.get())->getValue() == 1
            && static_cast<const NumberValue*>(z.get())->getValue() == 1;
}

VectorExpression &VectorExpression::operator=(const VectorExpression &other)
{
    if (other.x == nullptr) x = nullptr;
    else x = other.x->copy();
    if (other.y == nullptr) x = nullptr;
    else y = other.y->copy();
    if (other.z == nullptr) z = nullptr;
    else z = other.z->copy();
    return *this;
}

VectorExpression VectorExpression::operator/(const VectorExpression &other)
{
    return VectorExpression(make_unique<Division>(x->copy(), other.getX()->copy()), make_unique<Division>(y->copy(), other.getY()->copy()), make_unique<Division>(z->copy(), other.getZ()->copy()));
}

VectorExpression VectorExpression::operator/(const NumberValue &other)
{
    return VectorExpression(make_unique<Division>(x->copy(), other.copy()), make_unique<Division>(y->copy(), other.copy()), make_unique<Division>(z->copy(), other.copy()));
}

}
