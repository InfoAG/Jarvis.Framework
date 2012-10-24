#ifndef MAX_H
#define MAX_H

#include "AbstractBinaryOperation.h"
#include "NumberArith.h"

namespace CAS {

class Max : public AbstractBinaryOperation
{
public:
    Max(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual ExpressionP copy() const { return make_unique<Max>(*this); }

    virtual EvalRes eval(Scope &scope, bool lazy) const;
    virtual bool equals(const AbstractExpression *other) const;
    virtual std::string toString() const { return "max(" + first_op->toString() + "," + second_op->toString() + ")"; }
};

}

#endif // MAX_H
