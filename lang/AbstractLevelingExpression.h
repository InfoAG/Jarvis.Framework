#ifndef ABSTRACTLEVELINGEXPRESSION_H
#define ABSTRACTLEVELINGEXPRESSION_H

#include "AbstractExpression.h"

namespace CAS {

class AbstractLevelingExpression : public AbstractExpression
{
protected:
    Expressions operands;

public:
    AbstractLevelingExpression(ExpressionP first_op, ExpressionP second_op);
    AbstractLevelingExpression(const AbstractLevelingExpression &other);
    AbstractLevelingExpression(Expressions operands) : operands(std::move(operands)) {}

    virtual ExpressionP constructWithArgs(Expressions ops) const = 0;

    virtual ExpressionP substituteConstants() const;
    virtual bool hasVar(const std::string &id) const;
    virtual bool isSymbolic(Scope &scope) const;

    const Expressions &getOperands() const { return operands; }
    Expressions &getOperands() { return operands; }
};

}

#endif // ABSTRACTLEVELINGEXPRESSION_H
