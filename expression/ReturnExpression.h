#ifndef RETURNEXPRESSION_H
#define RETURNEXPRESSION_H

#include "AbstractUnaryOperation.h"

namespace CAS {

class ReturnExpression : public AbstractUnaryOperation
{
public:
    ReturnExpression(ExpressionP operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<ReturnExpression>(*this); }

    virtual ExpressionP execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { return "return " + operand->toString(); }
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif // RETURNEXPRESSION_H
