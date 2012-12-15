#include "NumberValue.h"
#include "List.h"
#include "Vector.h"

namespace CAS {

bool NumberValue::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(NumberValue) && static_cast<const NumberValue*>(other)->getValue() == value;
}

List NumberValue::operator/(const List &other)
{
    Expressions result;
    for (const auto &op : other.getOperands())
        result.emplace_back(make_unique<Division>(copyEx(), op->copyEx()));
    return List(std::move(result));
}

Vector NumberValue::operator/(const Vector &other)
{
    return Vector(make_unique<Division>(copyEx(), other.getX()->copyEx()), make_unique<Division>(copyEx(), other.getY()->copyEx()), make_unique<Division>(copyEx(), other.getZ()->copyEx()));
}

}
