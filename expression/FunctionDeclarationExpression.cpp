#include "FunctionDeclarationExpression.h"

namespace CAS {

TypeInfo FunctionDeclarationExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (candidates.contains(TypeInfo::VOID)) {
        if (! scope.hasFunc(sig)) scope.declareFunc(sig, returnType);
        return TypeInfo::VOID;
    } else throw "typing";
}

std::string FunctionDeclarationExpression::toString() const
{
    std::string result = returnType.toString() + " " + sig.id + "(";
    if (! sig.argumentTypes.empty()) {
        for (auto it = sig.argumentTypes.cbegin(); it != sig.argumentTypes.cend() - 1; ++it)
            result += it->toString() + ", ";
        result += sig.argumentTypes.back().toString();
    }
    return result + ")";
}

}
