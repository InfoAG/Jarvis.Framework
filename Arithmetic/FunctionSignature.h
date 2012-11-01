#ifndef FUNCTIONSIGNATURE_H
#define FUNCTIONSIGNATURE_H

#include "AbstractExpression.h"

namespace CAS {

struct FunctionSignature
{
    std::string id;
    std::vector<AbstractExpression::ReturnType> argumentTypes;

    bool operator<(const FunctionSignature &other) const { if (id == other.id) return argumentTypes < other.argumentTypes; else return id < other.id; }
};

}

#endif // FUNCTIONSIGNATURE_H
