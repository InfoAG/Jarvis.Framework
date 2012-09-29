#include "Modulo.h"

namespace CAS {

std::unique_ptr<AbstractExpression> Modulo::eval(Scope &scope, bool lazy) const
{
    auto first_op_result = first_op->eval(scope, lazy), second_op_result = second_op->eval(scope, lazy);
    if (typeid(first_op_result) == typeid(NumberArith) && typeid(second_op_result) == typeid(NumberArith))
        return make_unique<NumberArith>(*(static_cast<NumberArith*>(first_op_result.get())) % *(static_cast<NumberArith*>(second_op_result.get())));
    else return make_unique<Modulo>(std::move(first_op_result), std::move(second_op_result));
}

std::string Modulo::toString() const
{
    std::string result;
    if (typeid(*first_op) == typeid(Addition) || typeid(*first_op) == typeid(Subtraction) || typeid(*first_op) == typeid(Multiplication) || typeid(*first_op) == typeid(Division) || typeid(*first_op) == typeid(Assignment))
        result = "(" + first_op->toString() + ")";
    else result = first_op->toString();
    result += "%";
    if (typeid(*second_op) == typeid(Addition) || typeid(*second_op) == typeid(Subtraction) || typeid(*second_op) == typeid(Multiplication) || typeid(*second_op) == typeid(Division) || typeid(*second_op) == typeid(Assignment))
        return result + "(" + second_op->toString() + ")";
    else return result + second_op->toString();
}

bool Modulo::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(Modulo) && first_op->equals(static_cast<const Modulo*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const Modulo*>(other)->getSecondOp().get());
}

}
