#include "ScopeExpression.h"

namespace CAS {

AbstractExpression::EvalRes ScopeExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    Scope myScope(&scope);
    auto opRes = operand->eval(myScope, load, lazy, direct);
    return std::make_pair(opRes.first, std::move(opRes.second));
}

bool ScopeExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(ScopeExpression) && operand->equals(static_cast<const ScopeExpression*>(other)->getOperand().get());
}

}
