#include "Max.h"

namespace CAS {

std::unique_ptr<AbstractExpression> Max::eval(Scope &scope, bool lazy) const
{
    auto first_op_result = first_op->eval(scope, lazy), second_op_result = second_op->eval(scope, lazy);
    if (typeid(first_op_result) == typeid(NumberArith) && typeid(second_op_result) == typeid(NumberArith)) {
        if (static_cast<NumberArith*>(first_op_result.get())->getValue() > static_cast<NumberArith*>(second_op_result.get())->getValue())
            return first_op_result;
        else return second_op_result;
    } else return make_unique<Max>(std::move(first_op_result), std::move(second_op_result));
}

bool Max::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(Max) && first_op->equals(static_cast<const Max*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const Max*>(other)->getSecondOp().get());
}

}
