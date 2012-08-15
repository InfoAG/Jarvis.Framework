#include "Variable.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Variable::eval(const EvalInfo &ei) const
{
    EvalInfo::Definitions::const_iterator it;
    if ((it = ei.variables.find(identifier)) == ei.variables.end()) return copy();
    else return it->second->copy();
}

}
