#include "Variable.h"

namespace CAS {

std::unique_ptr<AbstractExpression> Variable::eval(Scope &scope, bool lazy) const
{
    if (! lazy && scope.hasVar(identifier)) {
        auto varDef = scope.getVar(identifier);
        if (varDef.second.evalFinished) return varDef.second.definition->copy();
        else return varDef.second.definition->eval(varDef.first, lazy);
    } else return copy();
}

bool Variable::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(Variable) && static_cast<const Variable*>(other)->getIdentifier() == identifier;
}

}
