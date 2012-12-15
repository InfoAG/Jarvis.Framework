#ifndef NEGATION_H
#define NEGATION_H

#include "AbstractUnaryExpression.h"
#include "BoolValue.h"

namespace CAS {

class Negation : public AbstractUnaryExpression
{
public:
    Negation(ExpressionP operand) : AbstractUnaryExpression(std::move(operand)) {}
    virtual StatementP copy() const { return make_unique<Negation>(*this); }
    virtual ExpressionP constructWithArgs(ExpressionP op) const { return make_unique<Negation>(std::move(op)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { return "!" + operand->toString(); }
    virtual bool equals(const AbstractStatement *other) const;
};

}

#endif // NEGATION_H
