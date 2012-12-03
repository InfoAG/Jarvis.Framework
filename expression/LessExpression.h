#ifndef LESSEXPRESSION_H
#define LESSEXPRESSION_H

#include "AbstractBinaryOperation.h"
#include "NumberValue.h"
#include "BoolValue.h"

namespace CAS {

class LessExpression : public AbstractBinaryOperation
{
public:
    LessExpression(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual ExpressionP copy() const { return make_unique<LessExpression>(*this); }

    virtual ExpressionP eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { return first_op->toString() + "<" + second_op->toString(); }
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif // LESSEXPRESSION_H
