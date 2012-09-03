#include "Division.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Division::eval(const EvalInfo &ei) const
{
    auto first_op_result = first_op->eval(ei), second_op_result = second_op->eval(ei);
    if (first_op_result->equals(second_op_result.get()))
        return make_unique<NumberArith>(1);
    else if (first_op_result->type() == NUMBERARITH && second_op_result->type() == NUMBERARITH)
        return make_unique<NumberArith>(*(static_cast<NumberArith*>(first_op_result.get())) / *(static_cast<NumberArith*>(second_op_result.get())));
    else if ((first_op_result->type() == NUMBERARITH && static_cast<NumberArith*>(first_op_result.get())->getValue() == 0)
             || (second_op_result->type() == NUMBERARITH && static_cast<NumberArith*>(second_op_result.get())->getValue() == 1))
        return first_op_result;
    else return make_unique<Division>(std::move(first_op_result), std::move(second_op_result));
}

bool Division::equals(const AbstractArithmetic *other) const
{
    if (other->type() != DIVISION) return false;
    const Division *casted = static_cast<const Division*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
