#include "Modulo.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Modulo::eval(const EvalInfo &ei) const
{
    auto first_op_result = first_op->eval(ei), second_op_result = second_op->eval(ei);
    if (first_op_result->type() == NUMBERARITH && second_op_result->type() == NUMBERARITH)
        return make_unique<NumberArith>(*(static_cast<NumberArith*>(first_op_result.get())) % *(static_cast<NumberArith*>(second_op_result.get())));
    else return Modulo(std::move(first_op_result), std::move(second_op_result)).eval(ei);
}

bool Modulo::equals(const AbstractArithmetic *other) const
{
    return other->type() == MODULO && first_op->equals(static_cast<const Modulo*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const Modulo*>(other)->getSecondOp().get());
}

}
