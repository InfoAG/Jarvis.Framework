#include "Max.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Max::eval(const EvalInfo &ei) const
{
    auto first_op_result = first_op->eval(ei), second_op_result = second_op->eval(ei);
    if (first_op_result->type() == NUMBERARITH && second_op_result->type() == NUMBERARITH)
        return make_unique<NumberArith>(static_cast<NumberArith*>(first_op_result.get())->getValue().max(static_cast<NumberArith*>(second_op_result.get())->getValue()));
    else return make_unique<Max>(std::move(first_op_result), std::move(second_op_result));
}

bool Max::equals(const AbstractArithmetic *other) const
{
    return other->type() == MAX && first_op->equals(static_cast<const Max*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const Max*>(other)->getSecondOp().get());
}

}
