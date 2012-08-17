#include "NumberArith.h"

namespace CAS {

std::string NumberArith::toString() const
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

bool NumberArith::isEqual(const AbstractArithmetic *other) const
{
    return other->getType() == AbstractArithmetic::NUMBERARITH && static_cast<const NumberArith*>(other)->getValue() == value;
}

}
