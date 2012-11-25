#include "VectorExpression.h"

namespace CAS {

inline AbstractExpression::EvalRes VectorExpression::eval(Scope &scope, const std::function<void (const std::string &)> &load, bool lazy, bool direct) const
{
    auto xRes = x->eval(scope, load, lazy, direct), yRes = y->eval(scope, load, lazy, direct), zRes = z->eval(scope, load, lazy, direct);
    if (xRes.first != TypeInfo::NUMBER || yRes.first != TypeInfo::NUMBER || zRes.first != TypeInfo::NUMBER) throw "typing";
    return std::make_pair(TypeInfo::VECTOR, make_unique<VectorExpression>(std::move(xRes.second), std::move(yRes.second), std::move(zRes.second)));
}

bool VectorExpression::isNull() const
{
    return typeid(*x) == typeid(NumberArith) && typeid(*y) == typeid(NumberArith) && typeid(*z) == typeid(NumberArith)
            && static_cast<const NumberArith*>(x.get())->getValue() == 0
            && static_cast<const NumberArith*>(y.get())->getValue() == 0
            && static_cast<const NumberArith*>(z.get())->getValue() == 0;
}

bool VectorExpression::isUnit() const
{
    return typeid(*x) == typeid(NumberArith) && typeid(*y) == typeid(NumberArith) && typeid(*z) == typeid(NumberArith)
            && static_cast<const NumberArith*>(x.get())->getValue() == 1
            && static_cast<const NumberArith*>(y.get())->getValue() == 1
            && static_cast<const NumberArith*>(z.get())->getValue() == 1;
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

}
