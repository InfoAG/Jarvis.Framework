#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "AbstractBinaryOperation.h"
#include "NumberArith.h"
#include "Addition.h"

namespace CAS {

class Subtraction : public AbstractBinaryOperation
{
public:
    Subtraction(std::unique_ptr<AbstractExpression> first_op, std::unique_ptr<AbstractExpression> second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<Subtraction>(*this); }

    virtual std::unique_ptr<AbstractExpression> eval(Scope &scope, bool lazy) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif //SUBTRACTION_H
