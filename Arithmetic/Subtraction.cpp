#include "Subtraction.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Subtraction::eval(const EvalInfo &ei) const
{
    auto first_op_result = first_op->eval(ei), second_op_result = second_op->eval(ei);
    if (first_op_result->getType() == NUMBERARITH && second_op_result->getType() == NUMBERARITH)
        return make_unique<NumberArith>(*(static_cast<NumberArith*>(first_op_result.get())) - *(static_cast<NumberArith*>(second_op_result.get())));
    else return Addition(std::move(first_op_result), make_unique<Multiplication>(make_unique<NumberArith>(-1), std::move(second_op_result))).eval(ei);
}

bool Subtraction::isEqual(const AbstractArithmetic *other) const
{
    if (other->getType() != SUBTRACTION) return false;
    const Subtraction *casted = static_cast<const Subtraction*>(other);
    return first_op->isEqual(casted->getFirstOp()) && second_op->isEqual(casted->getSecondOp());
}

}
