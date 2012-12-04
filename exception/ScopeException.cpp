#include "ScopeException.h"

namespace CAS {

std::string ScopeException::what() const
{
    std::string result = ((type == VAR) ? "variable " : "function ")
            + expr;
    if (reason == MissingDeclaration)
        return result + " was not declared in this scope.";
    else
        return result + " is already declared in this scope.";
}

}
