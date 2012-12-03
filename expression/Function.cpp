#include "Function.h"
#include "CFunctionBody.h"

namespace CAS {

AbstractExpression::ExpressionP Function::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    std::vector<ExpressionP> opResults;
    for (const auto &op : operands)
        opResults.emplace_back(op->eval(scope, load, lazy, direct));

    Scope::VarDefs funcVars;
    auto funcDefMatch = scope.getFunc({identifier, std::move(argTypes)});
    if (lazy || funcDefMatch.second.definition == nullptr)
        return copy();
    else {
        ExpressionP result;
        if (typeid(*(funcDefMatch.second.definition)) == typeid(CFunctionBody))
            result = static_cast<CFunctionBody*>(funcDefMatch.second.definition.get())->evalWithArgs(std::move(opResults), scope, load, lazy, direct);
        else {
            auto itOpResults = opResults.begin();
            auto itOpTypes = argTypes.cbegin();
            for (auto &funcVar : funcDefMatch.second.arguments)
                funcVars.insert(std::make_pair(std::move(funcVar), VariableDefinition{std::move(*(itOpResults++)), *(itOpTypes++)}));
            Scope funcScope(&funcDefMatch.first, std::move(funcVars));
            result = funcDefMatch.second.definition->eval(funcScope, load);
        }

        if (direct && ! result->isValue()) throw "directnonono";
        else return result;
    }
}

TypeInfo Function::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    auto opsAreDeterminant = true;
    for (const auto &op : operands) {
        try {
            argTypes.emplace_back(op->typeCheck(TypeCollection::all(), scope));
        } catch (const char *) {
            opsAreDeterminant = false;
            break;
        }
    }
    if (opsAreDeterminant) {
        FunctionSignature sig{identifier, argTypes};
        if (scope.hasFunc(sig)) {
            auto defMatch = scope.getFunc(sig).second.returnType;
            if (candidates.contains(defMatch)) return defMatch;
            else throw "typing";
        } else if (candidates.determinant()) {
            scope.declareFunc(sig, *(candidates.types.begin()));
            return *(candidates.types.begin());
        } else throw "typing";
    } else {
        bool foundOne = false;
        Scope matchScope;
        TypeInfo matchReturnT;
        for (const auto &func : scope.getFunctions()) {
            if (func.first.id == identifier && func.first.argumentTypes.size() == operands.size() && candidates.contains(func.second.returnType)) {
                auto sigTypesIt = func.first.argumentTypes.cbegin();
                Scope tryScope(&scope);
                for (const auto &op : operands) {
                    try {
                        auto opT = op->typeCheck({{*(sigTypesIt++)}}, tryScope);
                    } catch (const char *) { break; }
                }
                if (sigTypesIt == func.first.argumentTypes.cend()) {
                    if (foundOne) throw "typing";
                    else {
                        foundOne = true;
                        matchScope = std::move(tryScope);
                        matchReturnT = func.second.returnType;
                        argTypes = func.first.argumentTypes;
                    }
                }
            }
        }
        if (foundOne) {
            scope.consume(std::move(matchScope));
            return matchReturnT;
        } else throw "typing";
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
