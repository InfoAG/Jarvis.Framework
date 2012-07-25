#include "Addition.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Addition::eval(const EvalInfo &ei) const
{
    std::unique_ptr<AbstractArithmetic> first_op_result = first_op->eval(ei), second_op_result = second_op->eval(ei);
    if (first_op_result->getType() == NUMBERARITH && second_op_result->getType() == NUMBERARITH)
        return std::unique_ptr<NumberArith>(new NumberArith(*(static_cast<NumberArith*>(first_op.get())) + *(static_cast<NumberArith*>(second_op.get()))));
    else return std::unique_ptr<AbstractArithmetic>(new Addition(std::move(first_op_result), std::move(second_op_result)));
}

}
