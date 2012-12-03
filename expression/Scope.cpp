#include "Scope.h"
#include "AbstractExpression.h"

namespace CAS {

void Scope::declareVar(TypeInfo type, std::string id)
{
    if (variables.find(id) != variables.end()) throw "already there";
    //else if (parent && parent->hasVar(id)) parent->declareVar(type, std::move(id));
    else variables.insert(std::make_pair(std::move(id), VariableDefinition{type}));
}

void Scope::defineVar(const std::string &id, AbstractExpression::ExpressionP definition, bool recursion)
{
    auto it = variables.find(id);
    if (it != variables.end()) {
        it->second.definition = std::move(definition);
        it->second.recursion = recursion;
    } else if (parent && parent->hasVar(id)) parent->defineVar(id, std::move(definition));
    else throw "not declared";
    /*else if (var.type != AbstractExpression::NUMBER) throw ":O";
    else declareVar(AbstractExpression::NUMBER, id);
    variables.find(id)->second.definition = std::move(var.definition);*/
}

void Scope::declareFunc(FunctionSignature sig, TypeInfo returnType)
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

void Scope::consume(Scope other)
{
    for (auto &var : other.variables) {
        if (var.second.definition) {
            declareVar(std::move(var.second.type), var.first);
            defineVar(var.first, std::move(var.second.definition), var.second.recursion);
        } else
            declareVar(std::move(var.second.type), std::move(var.first));
    }
    for (auto &func : other.functions) {
        if (func.second.definition) {
            declareFunc(func.first, std::move(func.second.returnType));
            defineFunc(func.first, std::move(func.second));
        } else
            declareFunc(std::move(func.first), std::move(func.second.returnType));
    }
}

std::pair<Scope &, VariableDefinition&> Scope::getVar(const std::string &identifier)
{
    auto it = variables.find(identifier);
    if (it != variables.end()) return std::pair<Scope &, VariableDefinition &>(*this, it->second);
    else return parent->getVar(identifier);
}

std::pair<Scope &, FunctionDefinition &> Scope::getFunc(const FunctionSignature &sig)
{
    auto it = functions.find(sig);
    if (it != functions.end()) return std::pair<Scope &, FunctionDefinition&>(*this, it->second);
    else return parent->getFunc(sig);
}

}
