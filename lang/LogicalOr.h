#ifndef LOGICALOR_H
#define LOGICALOR_H

#include "AbstractBinaryExpression.h"
#include "BoolValue.h"

namespace CAS {

class LogicalOr : public AbstractBinaryExpression
{
public:
    LogicalOr(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryExpression(std::move(first_op), std::move(second_op)) {}
    virtual StatementP copy() const { return make_unique<LogicalOr>(*this); }
    virtual ExpressionP constructWithArgs(ExpressionP first, ExpressionP second) const { return make_unique<LogicalOr>(std::move(first), std::move(second)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { return first_op->toString() + "||" + second_op->toString(); }
    virtual bool equals(const AbstractStatement *other) const;
};

}

#endif // LOGICALOR_H
