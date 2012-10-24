#ifndef MIN_H
#define MIN_H

#include "AbstractBinaryOperation.h"
#include "NumberArith.h"

namespace CAS {

class Min : public AbstractBinaryOperation
{
public:
    Min(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual ExpressionP copy() const { return make_unique<Min>(*this); }

    virtual EvalRes eval(Scope &scope, bool lazy) const;
    virtual bool equals(const AbstractExpression *other) const;
    virtual std::string toString() const { return "min(" + first_op->toString() + "," + second_op->toString() + ")"; }
};

}

#endif // MIN_H
