#include "FactorialExpression.h"

namespace CAS {

AbstractExpression::EvalRes FactorialExpression::eval(Scope &scope, const std::function<void (const std::string &)> &load, bool lazy, bool direct) const
{
    auto opRes = operand->eval(scope, load, lazy, direct);
    if (opRes.first != TypeInfo::NUMBER) throw "type";

    double result = 1.0;
    int start = static_cast<NumberArith*>(opRes.second.get())->getValue();
    if (start < 0)
        while (start) result *= start++;
    else
        while (start) result *= start--;
    return std::make_pair(TypeInfo::NUMBER, make_unique<NumberArith>(result));
}

bool FactorialExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(FactorialExpression) && operand->equals(static_cast<const FactorialExpression*>(other)->getOperand().get());
}

}
