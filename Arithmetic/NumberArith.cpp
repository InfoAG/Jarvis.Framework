#include "NumberArith.h"

namespace CAS {

bool NumberArith::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(NumberArith) && static_cast<const NumberArith*>(other)->getValue() == value;
}

}
