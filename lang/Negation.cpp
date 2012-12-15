#include "Negation.h"

namespace CAS {

AbstractExpression::ExpressionP Negation::executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    auto operandRes = operand->executeExpression(scope, load, print, execOption);
    if (typeid(*(operandRes)) == typeid(BoolValue))
        return make_unique<BoolValue>(! static_cast<BoolValue*>(operandRes.get())->value());
    else return make_unique<Negation>(std::move(operandRes));
}

TypeInfo Negation::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::BOOL);
    operand->typeCheck({{TypeInfo::BOOL}}, scope);
    return TypeInfo::BOOL;
}

bool Negation::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(Negation) && operand->equals(static_cast<const Negation*>(other)->getOperand().get());
}

}
