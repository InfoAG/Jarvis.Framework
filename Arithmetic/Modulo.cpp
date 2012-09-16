#include "Modulo.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Modulo::eval(const EvalInfo &ei) const
{
    auto first_op_result = first_op->eval(ei), second_op_result = second_op->eval(ei);
    if (first_op_result->type() == NUMBERARITH && second_op_result->type() == NUMBERARITH)
        return make_unique<NumberArith>(*(static_cast<NumberArith*>(first_op_result.get())) % *(static_cast<NumberArith*>(second_op_result.get())));
    else return make_unique<Modulo>(std::move(first_op_result), std::move(second_op_result));
}

std::string Modulo::toString() const
{
    std::string result;
    if (first_op->type() == ADDITION || first_op->type() == SUBTRACTION || first_op->type() == MULTIPLICATION || first_op->type() == DIVISION || first_op->type() == ASSIGNMENT)
        result = "(" + first_op->toString() + ")";
    else result = first_op->toString();
    result += "%";
    if (second_op->type() == ADDITION || second_op->type() == SUBTRACTION || second_op->type() == MULTIPLICATION || second_op->type() == DIVISION || second_op->type() == ASSIGNMENT)
        return result + "(" + second_op->toString() + ")";
    else return result + second_op->toString();
}

bool Modulo::equals(const AbstractArithmetic *other) const
{
    return other->type() == MODULO && first_op->equals(static_cast<const Modulo*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const Modulo*>(other)->getSecondOp().get());
}

}
