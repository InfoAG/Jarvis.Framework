#include "Function.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Function::eval(const EvalInfo &ei) const
{
    EvalInfo::FuncDefs::const_iterator it = ei.functions.find(std::make_pair(identifier, operands.size()));
    if (it != ei.functions.end()) {
        EvalInfo includeFuncVars{ei.variables, ei.functions};
        auto itOperands = operands.cbegin();
        for (const auto &funcVar : it->second.first)
            includeFuncVars.funcVars[funcVar] = (*(itOperands++))->eval(ei);
        return it->second.second->eval(includeFuncVars);
    } else {
        Operands evaldOps;
        evaldOps.reserve(operands.size());
        for (const auto &operand : operands) evaldOps.emplace_back(operand->eval(ei));
        return make_unique<Function>(identifier, std::move(evaldOps));
    }
}

bool Function::equals(const AbstractArithmetic *other) const
{
    if (other->type() != FUNCTION) return false;
    return equalOperands(static_cast<const Function*>(other)->getOperands(), operands);
}

std::string Function::toString() const
{
    std::string result(identifier + "(" + operands.front()->toString());
    for (auto it = ++(operands.cbegin()); it != operands.cend(); ++it)
        result += "," + (*it)->toString();
    return result + ")";
}

}
