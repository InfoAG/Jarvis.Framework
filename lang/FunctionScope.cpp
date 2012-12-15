#include "FunctionScope.h"

namespace CAS {

bool FunctionScope::varIsSymbolic(const std::string &identifier)
{
    auto it = variables.find(identifier);
    if (it != variables.end()) return it->second.definition == nullptr || it->second.definition->isSymbolic(argumentScope);
    else return parent->varIsSymbolic(identifier);
}

std::pair<Scope &, VariableDefinition&> FunctionScope::getVar(const std::string &identifier)
{
    auto it = variables.find(identifier);
    if (it != variables.end()) return std::pair<Scope &, VariableDefinition &>(argumentScope, it->second);
    else return parent->getVar(identifier);
}

}
