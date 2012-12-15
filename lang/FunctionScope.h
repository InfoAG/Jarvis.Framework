#ifndef FUNCTIONSCOPE_H
#define FUNCTIONSCOPE_H

#include "Scope.h"

namespace CAS {

class FunctionScope : public Scope
{
private:
    Scope &argumentScope;

public:
    FunctionScope(Scope *parent, Scope &argumentScope, VarDefs variables) : Scope(parent, std::move(variables)), argumentScope(argumentScope) {}

    virtual bool varIsSymbolic(const std::string &identifier);
    virtual std::pair<Scope &, VariableDefinition &> getVar(const std::string &identifier);
};

}

#endif // FUNCTIONSCOPE_H
