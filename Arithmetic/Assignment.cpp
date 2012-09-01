#include "Assignment.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Assignment::eval(const EvalInfo &ei) const
{
    return make_unique<Assignment>(first_op->copy(), second_op->eval(ei));
}

bool Assignment::isEqual(const AbstractArithmetic *other) const
{
    if (other->getType() != ASSIGNMENT) return false;
    const Assignment *casted = static_cast<const Assignment*>(other);
    return first_op->isEqual(casted->getFirstOp()) && second_op->isEqual(casted->getSecondOp());
}

}
