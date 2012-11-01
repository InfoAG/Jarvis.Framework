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
    AbstractExpression::ReturnType returnType;

    FunctionDefinition(std::shared_ptr<AbstractExpression> definition, std::vector<std::string> arguments, AbstractExpression::ReturnType returnType) : definition(std::move(definition)), arguments(std::move(arguments)), returnType(returnType) {}
    FunctionDefinition(AbstractExpression::ReturnType returnType) : returnType(returnType) {}
};

}

#endif // FUNCTIONDEFINITION_H
