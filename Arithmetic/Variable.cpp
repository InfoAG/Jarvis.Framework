#include "Variable.h"

namespace CAS {

AbstractExpression::EvalRes Variable::eval(Scope &scope, bool lazy) const
{
    if (! lazy && scope.hasVar(identifier)) {
        auto varDef = scope.getVar(identifier);
        if (varDef.second.type != UNKNOWN) return std::make_pair(varDef.second.type, varDef.second.definition->copy());
        else return varDef.second.definition->eval(varDef.first, lazy);
    } else return std::make_pair(NUMBER, copy());
}

bool Variable::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(Variable) && static_cast<const Variable*>(other)->getIdentifier() == identifier;
}

}
