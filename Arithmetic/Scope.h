#ifndef SCOPE_H
#define SCOPE_H

#include <map>
#include <memory>
#include "VariableDefinition.h"
#include "FunctionDefinition.h"
#include "FunctionSignature.h"

namespace CAS {

class Scope
{
public:
    typedef std::map<std::string, VariableDefinition> VarDefs;
    typedef std::map<FunctionSignature, FunctionDefinition> FuncDefs;

private:
    Scope * const parent;

protected:
    VarDefs variables;
    FuncDefs functions;

public:
    Scope() : parent(nullptr) {}
    Scope(Scope * const parent) : parent(parent) {}
    Scope(Scope * const parent, VarDefs variables) : parent(parent), variables(std::move(variables)) {}

    virtual void declareVar(AbstractExpression::ReturnType type, std::string id);
    virtual void declareFunc(FunctionSignature sig, FunctionDefinition def);
    virtual void defineVar(const std::string &id, VariableDefinition var);
    //virtual void assignFunc(const std::pair<std::string, FunctionDefinition> &func);

    bool hasVar(const std::string &identifier) const { return variables.find(identifier) != variables.end() || (parent && parent->hasVar(identifier)); }
    std::pair<Scope &, const VariableDefinition&> getVar(const std::string &identifier);
    bool hasFunc(const FunctionSignature &sig) const { return functions.find(sig) != functions.end() || (parent && parent->hasFunc(sig)); }
    std::pair<Scope &, const FunctionDefinition&> getFunc(const FunctionSignature &sig);
};

}

#endif //SCOPE_H
