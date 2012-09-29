#ifndef FUNCTIONDEFINITION_H
#define FUNCTIONDEFINITION_H

#include "Definition.h"
#include <vector>
#include <string>

namespace CAS {

struct FunctionDefinition : public Definition
{
    std::vector<std::string> arguments;

    FunctionDefinition(std::vector<std::string> arguments, std::shared_ptr<AbstractExpression> definition, bool evalFinished) : Definition(std::move(definition), evalFinished), arguments(std::move(arguments)) {}
};

}

#endif // FUNCTIONDEFINITION_H
