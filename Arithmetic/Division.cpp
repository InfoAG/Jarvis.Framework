#include "Division.h"

namespace CAS {

std::unique_ptr<AbstractExpression> Division::eval(Scope &scope, bool lazy) const
{
    auto first_op_result = first_op->eval(scope, lazy), second_op_result = second_op->eval(scope, lazy);
    if (first_op_result->equals(second_op_result.get()))
        return make_unique<NumberArith>(1);
    else if (typeid(first_op_result) == typeid(NumberArith) && typeid(second_op_result) == typeid(NumberArith))
        return make_unique<NumberArith>(*(static_cast<NumberArith*>(first_op_result.get())) / *(static_cast<NumberArith*>(second_op_result.get())));
    else if ((typeid(first_op_result) == typeid(NumberArith) && static_cast<NumberArith*>(first_op_result.get())->getValue() == 0)
             || (typeid(second_op_result) == typeid(NumberArith) && static_cast<NumberArith*>(second_op_result.get())->getValue() == 1))
        return first_op_result;
    else return make_unique<Division>(std::move(first_op_result), std::move(second_op_result));
}

std::string Division::toString() const
{
    std::string result;
    if (typeid(*first_op) == typeid(Addition) || typeid(*first_op) == typeid(Subtraction))
        result = "(" + first_op->toString() + ")";
    else result = first_op->toString();
    result += "/";
    if (typeid(*second_op) == typeid(Addition) || typeid(*second_op) == typeid(Multiplication) || typeid(*second_op) == typeid(Division) || typeid(*second_op) == typeid(Subtraction)) return result + "(" + second_op->toString() + ")";
    else return result + second_op->toString();
}

bool Division::equals(const AbstractExpression *other) const
{
    if (typeid(*other) != typeid(Division)) return false;
    const Division *casted = static_cast<const Division*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
