#include "Function.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Function::eval(const EvalInfo &ei) const
{
    EvalInfo::FuncDefs::const_iterator it = ei.functions.find(std::make_pair(identifier, operands.size()));
    if (it != ei.functions.end()) {
        EvalInfo includeFuncVars(ei);
        Operands::const_iterator itOperands = operands.begin();
        for (const auto &funcVar : it->second.first)
            includeFuncVars.variables[funcVar] = (*(itOperands++))->eval(ei);
        return it->second.second->eval(includeFuncVars);
    } else return copy();
}

bool Function::isEqual(const AbstractArithmetic *other) const
{
    if (other->getType() != AbstractArithmetic::FUNCTION) return false;
    return equalOperands(static_cast<const Function*>(other)->getOperands(), operands);
}

std::string Function::toString() const
{
    std::string result(identifier + "(" + operands.front()->toString());
    for (Operands::const_iterator it = ++(operands.begin()); it != operands.end(); ++it)
        result += "," + (*it)->toString();
    return result + ")";
}

}
