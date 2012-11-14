#ifndef GREATEROREQUALEXPRESSION_H
#define GREATEROREQUALEXPRESSION_H

#include "AbstractBinaryOperation.h"
#include "NumberArith.h"
#include "BoolValue.h"

namespace CAS {

class GreaterOrEqualExpression : public AbstractBinaryOperation
{
public:
    GreaterOrEqualExpression(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual ExpressionP copy() const { return make_unique<GreaterOrEqualExpression>(*this); }

    virtual EvalRes eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
    virtual std::string toString() const { return first_op->toString() + ">=" + second_op->toString(); }
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif // GREATEROREQUALEXPRESSION_H
