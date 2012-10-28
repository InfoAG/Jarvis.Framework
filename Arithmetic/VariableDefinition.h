#ifndef VARIABLEDEFINITION_H
#define VARIABLEDEFINITION_H

#include "AbstractExpression.h"

namespace CAS {

struct VariableDefinition
{
    std::shared_ptr<AbstractExpression> definition;
    AbstractExpression::ReturnType type;

    VariableDefinition(std::shared_ptr<AbstractExpression> definition, AbstractExpression::ReturnType type) : definition(std::move(definition)), type(type) {}
    VariableDefinition(AbstractExpression::EvalRes evalRes) : definition(std::move(evalRes.second)), type(evalRes.first) {}
};

}

#endif // DEFINITION_H
