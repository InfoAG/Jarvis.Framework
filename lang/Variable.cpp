#include "Variable.h"

namespace CAS {

AbstractExpression::ExpressionP Variable::executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    auto varDef = scope.getVar(identifier);
    if (varDef.second.recursion) throw ExecutionException::recursion(identifier);
    else if (execOption == LAZY || (execOption != EAGER && varDef.second.definition == nullptr))
        return copyEx();
    else if (execOption == EAGER && (varDef.second.definition == nullptr || ! varDef.second.definition->isValue()))
        throw ExecutionException::failedEager(identifier);
    else {
        varDef.second.recursion = true;
        auto result = varDef.second.definition->executeExpression(varDef.first, load, print, execOption);
        varDef.second.recursion = false;
        return result;
    }
}



TypeInfo Variable::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (scope.hasVar(identifier)) {
        auto myT = scope.getVar(identifier).second.type;
        candidates.assertContains(*this, myT);
        return myT;
    } else {
        candidates.assertDeterminant(*this);
        scope.declareVar(*(candidates.types.begin()), identifier);
        return *(candidates.types.begin());
    }
}

AbstractExpression::ExpressionP Variable::differentiate(const std::string &var) const
{
    if (identifier == var)
        return make_unique<NumberValue>(1);
    else return make_unique<NumberValue>(0);
}

bool Variable::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(Variable) && static_cast<const Variable*>(other)->getIdentifier() == identifier;
}

}
