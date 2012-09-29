#include "Function.h"

namespace CAS {

std::unique_ptr<AbstractExpression> Function::eval(Scope &scope, bool lazy) const
{
    if (! lazy && scope.hasFunc(std::make_pair(identifier, operands.size()))) {
        Scope::VarDefs funcVars;
        auto funcDefMatch = scope.getFunc(std::make_pair(identifier, operands.size()));
        auto itOperands = operands.cbegin();
        for (const auto &funcVar : funcDefMatch.second.arguments)
            funcVars[funcVar] = Definition((*(itOperands++))->eval(scope, lazy), true);
        Scope funcScope(&funcDefMatch.first, std::move(funcVars));
        return funcDefMatch.second.definition->eval(funcScope);
    } else {
        Operands evaldOps;
        evaldOps.reserve(operands.size());
        for (const auto &operand : operands) evaldOps.emplace_back(operand->eval(scope, lazy));
        return make_unique<Function>(identifier, std::move(evaldOps));
    }
}

bool Function::equals(const AbstractExpression *other) const
{
    if (typeid(*other) != typeid(Function)) return false;
    return equalOperands(static_cast<const Function*>(other)->getOperands(), operands);
}

std::string Function::toString() const
{
    std::string result(identifier + "(" + operands.front()->toString());
    for (auto it = ++(operands.cbegin()); it != operands.cend(); ++it)
        result += "," + (*it)->toString();
    return result + ")";
}

}
