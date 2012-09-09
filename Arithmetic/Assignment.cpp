#include "Assignment.h"

namespace CAS {

bool Assignment::equals(const AbstractArithmetic *other) const
{
    if (other->type() != ASSIGNMENT) return false;
    const Assignment *casted = static_cast<const Assignment*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
