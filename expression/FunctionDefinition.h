#ifndef FUNCTIONDEFINITION_H
#define FUNCTIONDEFINITION_H

#include "AbstractExpression.h"
#include <vector>
#include <string>

namespace CAS {

struct FunctionDefinition
{
    AbstractExpression::ExpressionP definition;
    std::vector<std::string> arguments;
    TypeInfo returnType;
    bool defNeedsEval;

    FunctionDefinition(AbstractExpression::ExpressionP definition, std::vector<std::string> arguments, TypeInfo returnType, bool defNeedsEval = false) : definition(std::move(definition)), arguments(std::move(arguments)), returnType(std::move(returnType)), defNeedsEval(defNeedsEval) {}
    FunctionDefinition(std::unique_ptr<AbstractExpression> definition, TypeInfo returnType, bool defNeedsEval = false) : definition(std::move(definition)), returnType(returnType), defNeedsEval(defNeedsEval) {}
    FunctionDefinition(TypeInfo returnType) : returnType(std::move(returnType)) {}
    FunctionDefinition(const FunctionDefinition &other) : definition(other.definition ? other.definition->copy() : nullptr), arguments(other.arguments), returnType(other.returnType), defNeedsEval(other.defNeedsEval) {}
};

}

#endif // FUNCTIONDEFINITION_H
