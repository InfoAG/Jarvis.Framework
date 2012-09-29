#ifndef MIN_H
#define MIN_H

#include "AbstractBinaryOperation.h"
#include "NumberArith.h"

namespace CAS {

class Min : public AbstractBinaryOperation
{
public:
    Min(std::unique_ptr<AbstractExpression> first_op, std::unique_ptr<AbstractExpression> second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<Min>(*this); }

    virtual std::unique_ptr<AbstractExpression> eval(Scope &scope, bool lazy) const;
    virtual bool equals(const AbstractExpression *other) const;
    virtual std::string toString() const { return "min(" + first_op->toString() + "," + second_op->toString() + ")"; }
};

}

#endif // MIN_H
