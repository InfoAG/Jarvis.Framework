#include "Variable.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Variable::eval(const EvalInfo &ei) const
{
    ScopeInfo::VarDefs::const_iterator it;
    if (((it = ei.funcVars.find(identifier)) != ei.funcVars.end()) || ((it = ei.variables.find(identifier)) != ei.variables.end()))
        return it->second->eval({ei.variables, ei.functions});
    else return copy();
}

bool Variable::equals(const AbstractArithmetic *other) const
{
    return other->type() == VARIABLE && static_cast<const Variable*>(other)->getIdentifier() == identifier;
}

}
