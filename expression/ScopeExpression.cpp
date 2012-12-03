#include "ScopeExpression.h"

namespace CAS {

AbstractExpression::ExpressionP ScopeExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    Scope evalScope(myScope);
    evalScope.setParent(&scope);
    return operand->eval(evalScope, load, lazy, direct);
}

bool ScopeExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(ScopeExpression) && operand->equals(static_cast<const ScopeExpression*>(other)->getOperand().get());
}

}
