#include "NumberArith.h"

namespace CAS {

bool NumberArith::isEqual(const AbstractArithmetic *other) const
{
    return other->getType() == NUMBERARITH && static_cast<const NumberArith*>(other)->getValue() == value;
}

}
