#ifndef SCOPEEXPRESSION_H
#define SCOPEEXPRESSION_H

#include "AbstractUnaryOperation.h"
#include "Scope.h"
#include "OutputExpression.h"

namespace CAS {

class ScopeExpression : public AbstractUnaryOperation
{
private:
    Scope myScope;

public:
    ScopeExpression(ExpressionP operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<ScopeExpression>(*this); }

    virtual ExpressionP eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &) { return operand->typeCheck(candidates, myScope); }
    virtual std::string toString() const { return "{" + operand->toString() + "}"; }
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif // SCOPEEXPRESSION_H
