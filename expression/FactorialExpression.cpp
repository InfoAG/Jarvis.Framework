#include "FactorialExpression.h"

namespace CAS {

AbstractExpression::ExpressionP FactorialExpression::eval(Scope &scope, const std::function<void (const std::string &)> &load, bool lazy, bool direct) const
{
    auto opRes = operand->eval(scope, load, lazy, direct);
    if (typeid(*opRes) == typeid(NumberValue)) {
        double result = 1.0;
        int start = static_cast<NumberValue*>(opRes.get())->getValue();
        if (start < 0)
            while (start) result *= start++;
        else
            while (start) result *= start--;
        return make_unique<NumberValue>(result);
    } else return make_unique<FactorialExpression>(std::move(opRes));
}

TypeInfo FactorialExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (candidates.contains(TypeInfo::NUMBER)) {
        operand->typeCheck({{TypeInfo::NUMBER}}, scope);
        return TypeInfo::NUMBER;
    } else throw "typing";
}

bool FactorialExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(FactorialExpression) && operand->equals(static_cast<const FactorialExpression*>(other)->getOperand().get());
}

}
