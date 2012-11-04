#ifndef VARIABLEDEFINITION_H
#define VARIABLEDEFINITION_H

#include "AbstractExpression.h"

namespace CAS {

struct VariableDefinition
{
    std::shared_ptr<AbstractExpression> definition;
    TypeInfo type;

    VariableDefinition(std::shared_ptr<AbstractExpression> definition, TypeInfo type) : definition(std::move(definition)), type(std::move(type)) {}
    VariableDefinition(AbstractExpression::EvalRes evalRes) : definition(std::move(evalRes.second)), type(std::move(evalRes.first)) {}
};

}

#endif // DEFINITION_H
