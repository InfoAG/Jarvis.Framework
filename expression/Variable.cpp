#include "Variable.h"

namespace CAS {

AbstractExpression::ExpressionP Variable::execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const
{
    auto varDef = scope.getVar(identifier);
    if (varDef.second.recursion) throw ExecutionException::recursion(identifier);
    else if (execOption == LAZY || (execOption != EAGER && varDef.second.definition == nullptr))
        return copy();
    else if (execOption == EAGER && (varDef.second.definition == nullptr || ! varDef.second.definition->isValue()))
        throw ExecutionException::failedEager(identifier);
    else {
        varDef.second.recursion = true;
        auto result = varDef.second.definition->execute(scope, load, execOption);
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

bool Variable::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(Variable) && static_cast<const Variable*>(other)->getIdentifier() == identifier;
}

}
