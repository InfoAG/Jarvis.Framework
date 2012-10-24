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

    FunctionDefinition(std::vector<std::string> arguments, std::shared_ptr<AbstractExpression> definition) : definition(std::move(definition)), arguments(std::move(arguments)) {}
};

}

#endif // FUNCTIONDEFINITION_H
