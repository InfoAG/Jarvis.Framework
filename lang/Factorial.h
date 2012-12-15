#ifndef FACTORIAL_H
#define FACTORIAL_H

#include "AbstractUnaryExpression.h"
#include "NumberValue.h"

namespace CAS {

class Factorial : public AbstractUnaryExpression
{
public:
    Factorial(ExpressionP operand) : AbstractUnaryExpression(std::move(operand)) {}
    virtual StatementP copy() const { return make_unique<Factorial>(*this); }
    virtual ExpressionP constructWithArgs(ExpressionP op) const { return make_unique<Factorial>(std::move(op)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual bool equals(const AbstractStatement *other) const;
    virtual std::string toString() const { return operand->toString() + "!"; }
};

}

#endif // FACTORIAL_H
