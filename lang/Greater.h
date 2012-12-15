#ifndef GREATER_H
#define GREATER_H

#include "AbstractBinaryExpression.h"
#include "NumberValue.h"
#include "BoolValue.h"

namespace CAS {

class Greater : public AbstractBinaryExpression
{
public:
    Greater(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryExpression(std::move(first_op), std::move(second_op)) {}
    virtual StatementP copy() const { return make_unique<Greater>(*this); }
    virtual ExpressionP constructWithArgs(ExpressionP first, ExpressionP second) const { return make_unique<Greater>(std::move(first), std::move(second)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { return first_op->toString() + ">" + second_op->toString(); }
    virtual bool equals(const AbstractStatement *other) const;
};

}

#endif // GREATER_H
