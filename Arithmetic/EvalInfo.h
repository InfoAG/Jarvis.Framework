#ifndef EVALINFO_H
#define EVALINFO_H

#include "ScopeInfo.h"

namespace CAS {

struct EvalInfo : public ScopeInfo
{
    VarDefs funcVars;

    EvalInfo() {};
    EvalInfo(const ScopeInfo &scopeInfo) : ScopeInfo(scopeInfo) {}
    EvalInfo(const VarDefs &variables, const FuncDefs &functions) : ScopeInfo{variables, functions} {}
};

}

#endif //EVALINFO_H
