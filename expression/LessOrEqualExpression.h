#ifndef LESSOREQUALEXPRESSION_H
#define LESSOREQUALEXPRESSION_H

#include "AbstractBinaryOperation.h"
#include "NumberArith.h"
#include "BoolValue.h"

namespace CAS {

class LessOrEqualExpression : public AbstractBinaryOperation
{
public:
    LessOrEqualExpression(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual ExpressionP copy() const { return make_unique<LessOrEqualExpression>(*this); }

    virtual EvalRes eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
    virtual std::string toString() const { return first_op->toString() + "<=" + second_op->toString(); }
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif // LESSOREQUALEXPRESSION_H
