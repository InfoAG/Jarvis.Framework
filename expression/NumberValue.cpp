#include "NumberValue.h"
#include "List.h"
#include "VectorExpression.h"

namespace CAS {

bool NumberValue::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(NumberValue) && static_cast<const NumberValue*>(other)->getValue() == value;
}

List NumberValue::operator/(const List &other)
{
    Operands result;
    for (const auto &op : other.getOperands())
        result.emplace_back(make_unique<Division>(copy(), op->copy()));
    return List(std::move(result));
}

VectorExpression NumberValue::operator/(const VectorExpression &other)
{
    return VectorExpression(make_unique<Division>(copy(), other.getX()->copy()), make_unique<Division>(copy(), other.getY()->copy()), make_unique<Division>(copy(), other.getZ()->copy()));
}

}
