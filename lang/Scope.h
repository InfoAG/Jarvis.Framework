#ifndef SCOPE_H
#define SCOPE_H

#include <map>
#include <memory>
#include "VariableDefinition.h"
#include "FunctionDefinition.h"
#include "FunctionSignature.h"
#include "exception/ScopeException.h"
#include "exception/ExecutionException.h"

namespace CAS {

class Scope
{
public:
    typedef std::map<std::string, VariableDefinition> VarDefs;
    typedef std::map<FunctionSignature, FunctionDefinition> FuncDefs;

protected:
    Scope *parent;
    VarDefs variables;
    FuncDefs functions;

public:
    Scope() : parent(nullptr) {}
    Scope(Scope *parent) : parent(parent) {}
    Scope(Scope *parent, VarDefs variables) : parent(parent), variables(std::move(variables)) {}

    virtual void declareVar(TypeInfo type, std::string id);
    virtual void declareFunc(FunctionSignature sig, TypeInfo returnType);
    virtual void defineVar(const std::string &id, AbstractExpression::ExpressionP definition, bool recursion = false);
    virtual void defineFunc(const FunctionSignature &sig, std::vector<std::string> args, AbstractStatement::StatementP def);

    void consume(Scope other);

    bool hasVar(const std::string &identifier) const { return variables.find(identifier) != variables.end() || (parent && parent->hasVar(identifier)); }
    virtual bool varIsSymbolic(const std::string &identifier);
    virtual std::pair<Scope &, VariableDefinition &> getVar(const std::string &identifier);
    bool hasFunc(const FunctionSignature &sig) const { return functions.find(sig) != functions.end() || (parent && parent->hasFunc(sig)); }
    bool funcIsSymbolic(const FunctionSignature &sig) const;
    std::pair<Scope &, FunctionDefinition &> getFunc(const FunctionSignature &sig);

    void setParent(Scope *newParent) { parent = newParent; }
    const VarDefs &getVariables() const { return variables; }
    const FuncDefs &getFunctions() const { return functions; }
};

}

#endif //SCOPE_H
