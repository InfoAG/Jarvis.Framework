#ifndef VARIABLEDEFINITION_H
#define VARIABLEDEFINITION_H

#include "AbstractExpression.h"

namespace CAS {

struct VariableDefinition
{
    AbstractExpression::ExpressionP definition;
    TypeInfo type;
    bool recursion;

    VariableDefinition(AbstractExpression::ExpressionP definition, TypeInfo type, bool recursion = false) : definition(std::move(definition)), type(std::move(type)), recursion(recursion) {}
    VariableDefinition(TypeInfo type) : type(std::move(type)), recursion(false) {}
    VariableDefinition(const VariableDefinition &other) : definition(other.definition ? other.definition->copyEx() : nullptr), type(other.type), recursion(other.recursion) {}
};

}

#endif // DEFINITION_H
