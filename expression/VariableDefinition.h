#ifndef VARIABLEDEFINITION_H
#define VARIABLEDEFINITION_H

#include "AbstractExpression.h"

namespace CAS {

struct VariableDefinition
{
    std::shared_ptr<AbstractExpression> definition;
    TypeInfo type;
    bool recursion{false};

    VariableDefinition(std::shared_ptr<AbstractExpression> definition, TypeInfo type) : definition(std::move(definition)), type(std::move(type)), recursion(false) {}
    VariableDefinition(AbstractExpression::EvalRes evalRes) : definition(std::move(evalRes.second)), type(std::move(evalRes.first)), recursion(false) {}
    VariableDefinition(const VariableDefinition &other, bool recursion) : definition(other.definition), type(other.type), recursion(recursion) {}
};

}

#endif // DEFINITION_H
