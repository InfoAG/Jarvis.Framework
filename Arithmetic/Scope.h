#ifndef SCOPE_H
#define SCOPE_H

#include <map>
#include <memory>
#include "FunctionDefinition.h"

namespace CAS {

class AbstractExpression;

class Scope
{
public:
    typedef std::map<std::string, Definition> VarDefs;
    typedef std::map<std::pair<std::string, unsigned int>, FunctionDefinition> FuncDefs;

private:
    Scope * const parent;

protected:
    VarDefs variables;
    FuncDefs functions;

public:
    Scope() : parent(nullptr) {}
    Scope(Scope * const parent) : parent(parent) {}
    Scope(Scope * const parent, VarDefs variables) : parent(parent), variables(std::move(variables)) {}

    virtual void assignVar(const std::pair<std::string, Definition> &var);
    virtual void assignFunc(const std::pair<std::string, FunctionDefinition> &func);

    bool hasVar(const std::string &identifier) const { return variables.find(identifier) != variables.end() || (parent && parent->hasVar(identifier)); }
    std::pair<Scope &, const Definition&> getVar(const std::string &identifier);
    bool hasFunc(const std::pair<std::string, unsigned int> &idAndArgs) const { return functions.find(idAndArgs) != functions.end() || (parent && parent->hasFunc(idAndArgs)); }
    std::pair<Scope &, const FunctionDefinition&> getFunc(const std::pair<std::string, unsigned int> &idAndArgs);
};

}

#endif //SCOPE_H
