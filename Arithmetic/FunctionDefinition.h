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
    TypeInfo returnType;

    FunctionDefinition(std::shared_ptr<AbstractExpression> definition, std::vector<std::string> arguments, TypeInfo returnType) : definition(std::move(definition)), arguments(std::move(arguments)), returnType(std::move(returnType)) {}
    FunctionDefinition(TypeInfo returnType) : returnType(std::move(returnType)) {}
};

}

#endif // FUNCTIONDEFINITION_H
