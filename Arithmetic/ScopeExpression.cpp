#include "ScopeExpression.h"

namespace CAS {

std::unique_ptr<AbstractExpression> ScopeExpression::eval(Scope &scope, bool lazy) const
{
    Scope myScope(&scope);
    Operands result;
    for (const auto &op : operands) result.emplace_back(op->eval(myScope, lazy));
    return make_unique<ScopeExpression>(std::move(result));
}

std::string ScopeExpression::toString() const
{
    std::string result = "{";
    for (auto it = operands.cbegin(); it != operands.cend() - 1; ++it)
        result += (*it)->toString() + "\n";
    result += operands.back()->toString();
    return result + "}";
}

bool ScopeExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(ScopeExpression) && equalOperands(operands, static_cast<const ScopeExpression*>(other)->getOperands());
}

}
