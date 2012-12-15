#ifndef GREATEROREQUAL_H
#define GREATEROREQUAL_H

#include "AbstractBinaryExpression.h"
#include "NumberValue.h"
#include "BoolValue.h"

namespace CAS {

class GreaterOrEqual : public AbstractBinaryExpression
{
public:
    GreaterOrEqual(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryExpression(std::move(first_op), std::move(second_op)) {}
    virtual StatementP copy() const { return make_unique<GreaterOrEqual>(*this); }
    virtual ExpressionP constructWithArgs(ExpressionP first, ExpressionP second) const { return make_unique<GreaterOrEqual>(std::move(first), std::move(second)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { return first_op->toString() + ">=" + second_op->toString(); }
    virtual bool equals(const AbstractStatement *other) const;
};

}

#endif // GREATEROREQUAL_H
