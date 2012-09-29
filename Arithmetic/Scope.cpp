#include "Scope.h"
#include "AbstractExpression.h"

namespace CAS {

void Scope::assignVar(const std::pair<std::string, Definition> &var)
{
    auto it = variables.find(var.first);
    if (it != variables.end()) it->second = var.second;
    else if (parent && parent->hasVar(var.first)) parent->assignVar(var);
    else variables.insert(var);
}

void Scope::assignFunc(const std::pair<std::string, FunctionDefinition> &func)
{
    auto it = functions.find(std::make_pair(func.first, func.second.arguments.size()));
    if (it != functions.end()) it->second = func.second;
    else if (parent && parent->hasFunc(std::make_pair(func.first, func.second.arguments.size()))) parent->assignFunc(func);
    else functions.insert(std::make_pair(std::make_pair(func.first, func.second.arguments.size()), func.second));
}

std::pair<Scope &, const Definition&> Scope::getVar(const std::string &identifier)
{
    auto it = variables.find(identifier);
    if (it != variables.end()) return std::pair<Scope &, const Definition &>(*this, it->second);
    else return parent->getVar(identifier);
}

std::pair<Scope &, const FunctionDefinition&> Scope::getFunc(const std::pair<std::string, unsigned int> &idAndArgs)
{
    auto it = functions.find(idAndArgs);
    if (it != functions.end()) return std::pair<Scope &, const FunctionDefinition&>(*this, it->second);
    else return parent->getFunc(idAndArgs);
}

}
