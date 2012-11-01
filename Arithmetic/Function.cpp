#include "Function.h"

namespace CAS {

AbstractExpression::EvalRes Function::eval(Scope &scope, bool lazy) const
{
    std::vector<ReturnType> opTypes;
    std::vector<ExpressionP> opResults;
    for (const auto &op : operands) {
        auto result = op->eval(scope, lazy);
        opTypes.emplace_back(result.first);
        opResults.emplace_back(std::move(result.second));
    }
    FunctionSignature sig{identifier, opTypes};
    if (! lazy && scope.hasFunc(sig)) {
        Scope::VarDefs funcVars;
        auto funcDefMatch = scope.getFunc(sig);
        auto itOpResults = opResults.begin();
        auto itOpTypes = opTypes.cbegin();
        for (auto &funcVar : funcDefMatch.second.arguments)
            funcVars.insert(std::make_pair(std::move(funcVar), VariableDefinition{std::move(*(itOpResults++)), *(itOpTypes++)}));
        Scope funcScope(&funcDefMatch.first, std::move(funcVars));
        return funcDefMatch.second.definition->eval(funcScope);
    } else {
        Operands evaldOps;
        evaldOps.reserve(operands.size());
        for (const auto &operand : operands) evaldOps.emplace_back(operand->eval(scope, lazy).second);
        return std::make_pair(NUMBER, make_unique<Function>(identifier, std::move(evaldOps)));
    }
}

bool Function::equals(const AbstractExpression *other) const
{
    if (typeid(*other) != typeid(Function)) return false;
    return equalOperands(static_cast<const Function*>(other)->getOperands(), operands);
}

std::string Function::toString() const
{
    std::string result = identifier + "(";
    if (! operands.empty()) {
        result += operands.front()->toString();
        for (auto it = ++(operands.cbegin()); it != operands.cend(); ++it)
            result += "," + (*it)->toString();
    }
    return result + ")";
}

}
