#include "Subtraction.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Subtraction::eval(const EvalInfo &ei) const
{
    auto first_op_result = first_op->eval(ei), second_op_result = second_op->eval(ei);
    if (first_op_result->getType() == NUMBERARITH && second_op_result->getType() == NUMBERARITH)
        return make_unique<NumberArith>(*(static_cast<NumberArith*>(first_op_result.release())) + (NumberArith(-1) * *(static_cast<NumberArith*>(second_op_result.release()))));
    else return make_unique<Subtraction>(std::move(first_op_result), std::move(second_op_result));
}

bool Subtraction::isEqual(const AbstractArithmetic *other) const
{
    if (other->getType() != SUBTRACTION) return false;
    const Subtraction *casted = static_cast<const Subtraction*>(other);
    return first_op->isEqual(casted->getFirstOp()) && second_op->isEqual(casted->getSecondOp());
}

}
