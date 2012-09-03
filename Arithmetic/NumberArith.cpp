#include "NumberArith.h"

namespace CAS {

bool NumberArith::equals(const AbstractArithmetic *other) const
{
    return other->type() == NUMBERARITH && static_cast<const NumberArith*>(other)->getValue() == value;
}

}
