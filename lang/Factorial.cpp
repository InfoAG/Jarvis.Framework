#include "Factorial.h"

namespace CAS {

AbstractExpression::ExpressionP Factorial::executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    auto opRes = operand->executeExpression(scope, load, print, execOption);
    if (typeid(*opRes) == typeid(NumberValue)) {
        double result = 1.0;
        int start = static_cast<NumberValue*>(opRes.get())->getValue();
        if (start < 0)
            while (start) result *= start++;
        else
            while (start) result *= start--;
        return make_unique<NumberValue>(result);
    } else return make_unique<Factorial>(std::move(opRes));
}

TypeInfo Factorial::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::NUMBER);
    operand->typeCheck({{TypeInfo::NUMBER}}, scope);
    return TypeInfo::NUMBER;
}

bool Factorial::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(Factorial) && operand->equals(static_cast<const Factorial*>(other)->getOperand().get());
}

}
