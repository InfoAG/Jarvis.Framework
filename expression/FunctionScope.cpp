#include "FunctionScope.h"

namespace CAS {

std::pair<Scope &, VariableDefinition&> FunctionScope::getVar(const std::string &identifier)
{
    auto it = variables.find(identifier);
    if (it != variables.end()) return std::pair<Scope &, VariableDefinition &>(argumentScope, it->second);
    else return parent->getVar(identifier);
}

}
