#include "Assignment.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Assignment::eval(const EvalInfo &ei) const
{
    return make_unique<Assignment>(first_op->copy(), second_op->eval(ei));
}

bool Assignment::equals(const AbstractArithmetic *other) const
{
    if (other->type() != ASSIGNMENT) return false;
    const Assignment *casted = static_cast<const Assignment*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
