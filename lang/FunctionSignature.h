#ifndef FUNCTIONSIGNATURE_H
#define FUNCTIONSIGNATURE_H

#include "AbstractStatement.h"

namespace CAS {

struct FunctionSignature
{
    std::string id;
    std::vector<TypeInfo> argumentTypes;

    std::string toString() const;

    bool operator==(const FunctionSignature &other) const { return id == other.id && argumentTypes == other.argumentTypes; }
    bool operator<(const FunctionSignature &other) const;
};

}

#endif // FUNCTIONSIGNATURE_H
