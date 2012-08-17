#include "Variable.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Variable::eval(const EvalInfo &ei) const
{
    EvalInfo::Definitions::const_iterator it;
    if ((it = ei.variables.find(identifier)) == ei.variables.end()) return copy();
    else return it->second->copy();
}

bool Variable::isEqual(const AbstractArithmetic *other) const
{
    return other->getType() == AbstractArithmetic::VARIABLE && static_cast<const Variable*>(other)->getIdentifier() == identifier;
}

}
