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
    bool defNeedsEval;

    FunctionDefinition(std::shared_ptr<AbstractExpression> definition, std::vector<std::string> arguments, TypeInfo returnType, bool defNeedsEval = false) : definition(std::move(definition)), arguments(std::move(arguments)), returnType(std::move(returnType)), defNeedsEval(defNeedsEval) {}
    FunctionDefinition(std::shared_ptr<AbstractExpression> definition, TypeInfo returnType, bool defNeedsEval = false) : definition(std::move(definition)), returnType(returnType), defNeedsEval(defNeedsEval) {}
    FunctionDefinition(TypeInfo returnType) : returnType(std::move(returnType)) {}
};

}

#endif // FUNCTIONDEFINITION_H
