#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "AbstractBinaryOperation.h"
#include "NumberValue.h"
#include "Addition.h"

namespace CAS {

class Subtraction : public AbstractBinaryOperation
{
public:
    Subtraction(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual ExpressionP copy() const { return make_unique<Subtraction>(*this); }

    virtual ExpressionP execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif //SUBTRACTION_H
