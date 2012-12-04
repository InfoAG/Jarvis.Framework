#ifndef GREATEREXPRESSION_H
#define GREATEREXPRESSION_H

#include "AbstractBinaryOperation.h"
#include "NumberValue.h"
#include "BoolValue.h"

namespace CAS {

class GreaterExpression : public AbstractBinaryOperation
{
public:
    GreaterExpression(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual ExpressionP copy() const { return make_unique<GreaterExpression>(*this); }

    virtual ExpressionP execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { return first_op->toString() + ">" + second_op->toString(); }
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif // GREATEREXPRESSION_H
