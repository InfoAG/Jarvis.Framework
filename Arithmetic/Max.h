#ifndef MAX_H
#define MAX_H

#include "AbstractBinaryOperation.h"
#include "NumberArith.h"

namespace CAS {

class Max : public AbstractBinaryOperation
{
public:
    Max(std::unique_ptr<AbstractExpression> first_op, std::unique_ptr<AbstractExpression> second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<Max>(*this); }

    virtual std::unique_ptr<AbstractExpression> eval(Scope &scope, bool lazy) const;
    virtual bool equals(const AbstractExpression *other) const;
    virtual std::string toString() const { return "max(" + first_op->toString() + "," + second_op->toString() + ")"; }
};

}

#endif // MAX_H
