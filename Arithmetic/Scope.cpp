#include "Scope.h"
#include "AbstractExpression.h"

namespace CAS {

void Scope::declareVar(AbstractExpression::ReturnType type, std::string id)
{
    if (variables.find(id) != variables.end()) throw "already there";
    //else if (parent && parent->hasVar(id)) parent->declareVar(type, std::move(id));
    else variables.insert(std::make_pair(std::move(id), VariableDefinition{nullptr, type}));
}

void Scope::defineVar(const std::string &id, VariableDefinition var)
{
    auto it = variables.find(id);
    if (it != variables.end()) {
        if (it->second.type != var.type) throw "oh snap!";
        else it->second.definition = var.definition;
    } else if (parent && parent->hasVar(id)) parent->defineVar(id, var);
    else throw "not declared";
    /*else if (var.type != AbstractExpression::NUMBER) throw ":O";
    else declareVar(AbstractExpression::NUMBER, id);
    variables.find(id)->second.definition = std::move(var.definition);*/
}

void Scope::declareFunc(FunctionSignature sig, AbstractExpression::ReturnType returnType)
{
    if (functions.find(sig) != functions.end()) throw "already there";
    else functions.insert(std::make_pair(std::move(sig), FunctionDefinition{returnType}));
}

void Scope::defineFunc(const FunctionSignature &sig, FunctionDefinition def)
{
    auto it = functions.find(sig);
    if (it != functions.end()) {
        if (it->second.returnType != def.returnType) throw "ambiguous return type";
        else it->second = std::move(def);
    } else if (parent && parent->hasFunc(sig)) parent->defineFunc(sig, std::move(def));
    else throw "not declared";
}

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

}
