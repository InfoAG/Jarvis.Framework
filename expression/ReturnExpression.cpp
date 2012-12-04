#include "ReturnExpression.h"

namespace CAS {

AbstractExpression::ExpressionP ReturnExpression::execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const
{
    return make_unique<ReturnExpression>(operand->execute(scope, load, execOption));
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
