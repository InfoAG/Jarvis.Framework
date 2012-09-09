#include "Subtraction.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Subtraction::eval(const EvalInfo &ei) const
{
    auto first_op_result = first_op->eval(ei), second_op_result = second_op->eval(ei);
    if (first_op_result->type() == NUMBERARITH && second_op_result->type() == NUMBERARITH)
        return make_unique<NumberArith>(*(static_cast<NumberArith*>(first_op_result.get())) - *(static_cast<NumberArith*>(second_op_result.get())));
    else return Addition(std::move(first_op_result), make_unique<Multiplication>(make_unique<NumberArith>(-1), std::move(second_op_result))).eval(ei);
}

std::string Subtraction::toString() const
{
    std::string result;
    if (first_op->type() == ADDITION)
        result = "(" + first_op->toString() + ")";
    else result = first_op->toString();
    result += "-";
    if (second_op->type() == ADDITION || second_op->type() == SUBTRACTION) return result + "(" + second_op->toString() + ")";
    else return result + second_op->toString();
}

bool Subtraction::equals(const AbstractArithmetic *other) const
{
    if (other->type() != SUBTRACTION) return false;
    const Subtraction *casted = static_cast<const Subtraction*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
