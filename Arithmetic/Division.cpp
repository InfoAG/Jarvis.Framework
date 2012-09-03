#include "Division.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Division::eval(const EvalInfo &ei) const
{
    auto first_op_result = first_op->eval(ei), second_op_result = second_op->eval(ei);
    if (first_op_result->isEqual(second_op_result.get()))
        return make_unique<NumberArith>(1);
    else if (first_op_result->getType() == NUMBERARITH && second_op_result->getType() == NUMBERARITH)
        return make_unique<NumberArith>(*(static_cast<NumberArith*>(first_op_result.get())) / *(static_cast<NumberArith*>(second_op_result.get())));
    else if (first_op_result->getType() == NUMBERARITH && static_cast<NumberArith*>(first_op_result.get())->getValue() == 0)
        return first_op_result;
    else if (second_op_result->getType() == NUMBERARITH && static_cast<NumberArith*>(second_op_result.get())->getValue() == 1)
        return second_op_result;
    else return make_unique<Division>(std::move(first_op_result), std::move(second_op_result));
}

bool Division::isEqual(const AbstractArithmetic *other) const
{
    if (other->getType() != DIVISION) return false;
    const Division *casted = static_cast<const Division*>(other);
    return first_op->isEqual(casted->getFirstOp()) && second_op->isEqual(casted->getSecondOp());
}

}
