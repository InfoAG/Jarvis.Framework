#include "Function.h"
#include "CFunctionBody.h"

namespace CAS {

AbstractExpression::EvalRes Function::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    std::vector<TypeInfo> opTypes;
    std::vector<ExpressionP> opResults;
    for (const auto &op : operands) {
        auto result = op->eval(scope, load, lazy, direct);
        opTypes.emplace_back(result.first);
        opResults.emplace_back(std::move(result.second));
    }
    FunctionSignature sig{identifier, opTypes};
    if (scope.hasFunc(sig)) {
        Scope::VarDefs funcVars;
        auto funcDefMatch = scope.getFunc(sig);
        if (lazy || funcDefMatch.second.definition == nullptr)
            return std::make_pair(funcDefMatch.second.returnType, copy());
        else {
            EvalRes result;
            if (typeid(*(funcDefMatch.second.definition)) == typeid(CFunctionBody))
                result = static_cast<CFunctionBody*>(funcDefMatch.second.definition.get())->evalWithArgs(std::move(opResults), scope, load, lazy, direct);
            else {
                auto itOpResults = opResults.begin();
                auto itOpTypes = opTypes.cbegin();
                for (auto &funcVar : funcDefMatch.second.arguments)
                    funcVars.insert(std::make_pair(std::move(funcVar), VariableDefinition{std::move(*(itOpResults++)), *(itOpTypes++)}));
                Scope funcScope(&funcDefMatch.first, std::move(funcVars));
                result = funcDefMatch.second.definition->eval(funcScope, load);
            }
            if (result.first != funcDefMatch.second.returnType) throw "return type";
            else if (direct && ! result.second->isValue()) throw "directnonono";
            else return result;
        }
    } else {
        Operands evaldOps;
        evaldOps.reserve(operands.size());
        for (const auto &operand : operands) evaldOps.emplace_back(operand->eval(scope, load, lazy, direct).second);
        return std::make_pair(TypeInfo{TypeInfo::NUMBER}, make_unique<Function>(identifier, std::move(evaldOps)));
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
