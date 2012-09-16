#include "Min.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Min::eval(const EvalInfo &ei) const
{
    auto first_op_result = first_op->eval(ei), second_op_result = second_op->eval(ei);
    if (first_op_result->type() == NUMBERARITH && second_op_result->type() == NUMBERARITH)
        return make_unique<NumberArith>(static_cast<NumberArith*>(first_op_result.get())->getValue().min(static_cast<NumberArith*>(second_op_result.get())->getValue()));
    else return make_unique<Min>(std::move(first_op_result), std::move(second_op_result));
}

bool Min::equals(const AbstractArithmetic *other) const
{
    return other->type() == MIN && first_op->equals(static_cast<const Min*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const Min*>(other)->getSecondOp().get());
}

}
