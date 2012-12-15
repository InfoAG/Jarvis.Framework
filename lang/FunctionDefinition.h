#ifndef FUNCTIONDEFINITION_H
#define FUNCTIONDEFINITION_H

#include "AbstractStatement.h"
#include <vector>
#include <string>

namespace CAS {

struct FunctionDefinition
{
    AbstractStatement::StatementP definition;
    std::vector<std::string> arguments;
    TypeInfo returnType;

    FunctionDefinition(AbstractStatement::StatementP definition, std::vector<std::string> arguments, TypeInfo returnType) : definition(std::move(definition)), arguments(std::move(arguments)), returnType(std::move(returnType)) {}
    FunctionDefinition(AbstractStatement::StatementP definition, TypeInfo returnType) : definition(std::move(definition)), returnType(returnType) {}
    FunctionDefinition(TypeInfo returnType) : returnType(std::move(returnType)) {}
    FunctionDefinition(const FunctionDefinition &other) : definition(other.definition ? other.definition->copy() : nullptr), arguments(other.arguments), returnType(other.returnType) {}
};

}

#endif // FUNCTIONDEFINITION_H
