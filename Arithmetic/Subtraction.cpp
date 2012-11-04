#include "Subtraction.h"

namespace CAS {

AbstractExpression::EvalRes Subtraction::eval(Scope &scope, bool lazy) const
{
    auto first_op_result = first_op->eval(scope, lazy), second_op_result = second_op->eval(scope, lazy);
    if (typeid(first_op_result) == typeid(NumberArith) && typeid(second_op_result) == typeid(NumberArith))
        return std::make_pair(TypeInfo{TypeInfo::NUMBER}, make_unique<NumberArith>(*(static_cast<NumberArith*>(first_op_result.second.get())) - *(static_cast<NumberArith*>(second_op_result.second.get()))));
    else return Addition(std::move(first_op_result.second), make_unique<LevelMultiplication>(make_unique<NumberArith>(-1), std::move(second_op_result.second))).eval(scope, lazy);
}

std::string Subtraction::toString() const
{
    std::string result;
    if (typeid(*first_op) == typeid(Addition))
        result = "(" + first_op->toString() + ")";
    else result = first_op->toString();
    result += "-";
    if (typeid(*second_op) == typeid(Addition) || typeid(*second_op) == typeid(Subtraction)) return result + "(" + second_op->toString() + ")";
    else return result + second_op->toString();
}

bool Subtraction::equals(const AbstractExpression *other) const
{
    if (typeid(*other) != typeid(Subtraction)) return false;
    const Subtraction *casted = static_cast<const Subtraction*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
