#include "ScopeExpression.h"

namespace CAS {

AbstractExpression::ExpressionP ScopeExpression::execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const
{
    Scope evalScope(myScope);
    evalScope.setParent(&scope);
    return operand->execute(evalScope, load, execOption);
}

bool ScopeExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(ScopeExpression) && operand->equals(static_cast<const ScopeExpression*>(other)->getOperand().get());
}

}
