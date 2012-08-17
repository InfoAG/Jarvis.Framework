#include "Division.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Division::eval(const EvalInfo &ei) const
{
    std::unique_ptr<AbstractArithmetic> first_op_result = first_op->eval(ei), second_op_result = second_op->eval(ei);
    if (first_op_result->getType() == NUMBERARITH && second_op_result->getType() == NUMBERARITH)
        return std::unique_ptr<NumberArith>(new NumberArith(*(static_cast<NumberArith*>(first_op_result.release())) / *(static_cast<NumberArith*>(second_op_result.release()))));
    else
        return std::unique_ptr<AbstractArithmetic>(new Division(std::move(first_op_result), std::move(second_op_result)));
}

bool Division::isEqual(const AbstractArithmetic *other) const
{
    if (other->getType() != AbstractArithmetic::DIVISION) return false;
    const Division *casted = static_cast<const Division*>(other);
    return first_op->isEqual(casted->getFirstOp()) && second_op->isEqual(casted->getSecondOp());
}

}
