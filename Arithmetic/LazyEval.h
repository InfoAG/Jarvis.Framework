#ifndef LAZYEVAL_H
#define LAZYEVAL_H

#include "AbstractUnaryOperation.h"

namespace CAS {

class LazyEval : public AbstractUnaryOperation
{
public:
    LazyEval(ExpressionP operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual ExpressionP copy() const { return make_unique<LazyEval>(*this); }

    virtual EvalRes eval(Scope &scope, bool) const { return operand->eval(scope, true); }
    virtual bool equals(const AbstractExpression *other) const;
    virtual std::string toString() const { return "lazy(" + operand->toString() + ")"; }
};

}

#endif // LAZYEVAL_H
