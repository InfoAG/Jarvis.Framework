#include "Scope.h"
#include "AbstractExpression.h"

namespace CAS {

void Scope::defineVar(const std::string &id, VariableDefinition var)
{
    auto it = variables.find(id);
    if (it != variables.end()) {
        if (it->second.type != var.type) throw "oh snap!";
        else it->second.definition = var.definition;
    } else if (parent && parent->hasVar(id)) parent->defineVar(id, var);
    else if (var.type != AbstractExpression::NUMBER) throw ":O";
    else declareVar(AbstractExpression::NUMBER, id);
    variables.find(id)->second.definition = std::move(var.definition);
}

/*
void Scope::assignFunc(const std::pair<std::string, FunctionDefinition> &func)
{
    auto it = functions.find(std::make_pair(func.first, func.second.arguments.size()));
    if (it != functions.end()) it->second = func.second;
    else if (parent && parent->hasFunc(std::make_pair(func.first, func.second.arguments.size()))) parent->assignFunc(func);
    else functions.insert(std::make_pair(std::make_pair(func.first, func.second.arguments.size()), func.second));
}
*/

std::pair<Scope &, const VariableDefinition&> Scope::getVar(const std::string &identifier)
{
    auto it = variables.find(identifier);
    if (it != variables.end()) return std::pair<Scope &, const VariableDefinition &>(*this, it->second);
    else return parent->getVar(identifier);
}

std::pair<Scope &, const FunctionDefinition&> Scope::getFunc(const FunctionSignature &sig)
{
    auto it = functions.find(sig);
    if (it != functions.end()) return std::pair<Scope &, const FunctionDefinition&>(*this, it->second);
    else return parent->getFunc(sig);
}

void Scope::declareVar(AbstractExpression::ReturnType type, std::string id)
{
    auto it = variables.find(id);
    if (it != variables.end()) throw "already there";
    //else if (parent && parent->hasVar(id)) parent->declareVar(type, std::move(id));
    else variables.insert(std::make_pair(std::move(id), VariableDefinition{nullptr, type}));
}

void Scope::declareFunc(FunctionSignature sig, FunctionDefinition def)
{
    /*
    std::vector<AbstractExpression::ReturnType> argSigs;
    for (const auto &it : arguments) argSigs.emplace_back(it.first);
    FunctionSignature sig{std::move(id), std::move(argSigs)};
    */
    auto it = functions.find(sig);
    if (it != functions.end()) it->second = def;
    else if (parent && parent->hasFunc(sig)) parent->declareFunc(std::move(sig), std::move(def));
    else functions.insert(std::make_pair(std::move(sig), std::move(def)));
}

}
