#include "ReturnExpression.h"

namespace CAS {

AbstractExpression::ExpressionP ReturnExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    return make_unique<ReturnExpression>(operand->eval(scope, load, lazy, direct));
}

TypeInfo ReturnExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    TypeCollection tc(candidates);
    tc.types.erase(TypeInfo::VOID);
    return operand->typeCheck(tc, scope);
}

bool ReturnExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(ReturnExpression) && operand->equals(static_cast<const ReturnExpression*>(other)->getOperand().get());
}

}
