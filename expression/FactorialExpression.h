#ifndef FACTORIALEXPRESSION_H
#define FACTORIALEXPRESSION_H

#include "AbstractUnaryOperation.h"
#include "NumberValue.h"

namespace CAS {

class FactorialExpression : public AbstractUnaryOperation
{
public:
    FactorialExpression(ExpressionP operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual ExpressionP copy() const { return make_unique<FactorialExpression>(*this); }

    virtual ExpressionP execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption direct) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual bool equals(const AbstractExpression *other) const;
    virtual std::string toString() const { return operand->toString() + "!"; }
};

}

#endif // FACTORIALEXPRESSION_H
