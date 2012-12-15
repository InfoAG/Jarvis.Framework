#include "Function.h"
#include "CFunctionBody.h"

namespace CAS {

AbstractExpression::ExpressionP Function::executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    std::vector<ExpressionP> opResults;
    for (const auto &op : operands)
        opResults.emplace_back(op->executeExpression(scope, load, print, execOption));

    auto funcDefMatch = scope.getFunc({identifier, argTypes});
    if (execOption == LAZY || funcDefMatch.second.definition == nullptr)
        return make_unique<Function>(*this);
    else {
        ExpressionP result;
        if (typeid(*(funcDefMatch.second.definition)) == typeid(CFunctionBody)) {
            result = static_cast<CFunctionBody*>(funcDefMatch.second.definition.get())->executeWithArgs(std::move(opResults), scope, load, print, execOption);
            if (result == nullptr) result = make_unique<Function>(identifier, std::move(opResults), argTypes);
        } else {
            Scope::VarDefs funcVars;
            auto itOpResults = opResults.begin();
            auto itOpTypes = argTypes.cbegin();
            for (const auto &funcVar : funcDefMatch.second.arguments)
                funcVars.insert(std::make_pair(funcVar, VariableDefinition{std::move(*(itOpResults++)), *(itOpTypes++)}));
            FunctionScope funcArgScope(&funcDefMatch.first, scope, std::move(funcVars));
            Scope funcBodyScope(&funcArgScope);
            result = funcDefMatch.second.definition->execute(funcBodyScope, load, print);
        }

        if (execOption == EAGER && ! result->isValue()) throw ExecutionException::failedEager(toString());
        else return result;
    }
}

TypeInfo Function::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    auto opsAreDeterminant = true;
    for (const auto &op : operands) {
        try {
            argTypes.emplace_back(op->typeCheck(TypeCollection::all(), scope));
        } catch (UndecidableTypeException &) {
            opsAreDeterminant = false;
            break;
        }
    }
    if (opsAreDeterminant) {
        FunctionSignature sig{identifier, argTypes};
        if (scope.hasFunc(sig)) {
            auto defMatch = scope.getFunc(sig).second.returnType;
            candidates.assertContains(*this, defMatch);
            return defMatch;
        } else {
            candidates.assertDeterminant(*this);
            scope.declareFunc(sig, *(candidates.types.begin()));
            return *(candidates.types.begin());
        }
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
                    } catch (const UndecidableTypeException &) { break; }
                }
                if (sigTypesIt == func.first.argumentTypes.cend()) {
                    if (foundOne) throw UndecidableTypeException(toString());
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
        } else throw UndecidableTypeException(toString());
    }
}

bool Function::equals(const AbstractStatement *other) const
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
