#ifndef FUNCTIONDECLARATIONINFO_H
#define FUNCTIONDECLARATIONINFO_H

#include "FunctionSignature.h"

namespace CAS {

struct FunctionDeclarationInfo : public FunctionSignature
{
    TypeInfo returnType;

    FunctionDeclarationInfo(FunctionSignature sig, TypeInfo returnType) : FunctionSignature(std::move(sig)), returnType(std::move(returnType)) {}
};

}

#endif // FUNCTIONDECLARATIONINFO_H
