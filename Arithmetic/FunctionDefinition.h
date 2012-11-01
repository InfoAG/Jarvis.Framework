#ifndef FUNCTIONDEFINITION_H
#define FUNCTIONDEFINITION_H

#include "AbstractExpression.h"
#include <vector>
#include <string>

namespace CAS {

struct FunctionDefinition
{
    std::shared_ptr<AbstractExpression> definition;
    std::vector<std::string> arguments;
    CAS::AbstractExpression::ReturnType returnType;

    FunctionDefinition(AbstractExpression::ReturnType returnType) : returnType(returnType) {}
};

}

#endif // FUNCTIONDEFINITION_H
