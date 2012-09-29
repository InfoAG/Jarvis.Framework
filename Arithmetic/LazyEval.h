#ifndef LAZYEVAL_H
#define LAZYEVAL_H

#include "AbstractUnaryOperation.h"

namespace CAS {

class LazyEval : public AbstractUnaryOperation
{
public:
    LazyEval(std::unique_ptr<AbstractExpression> operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<LazyEval>(*this); }

    virtual std::unique_ptr<AbstractExpression> eval(Scope &scope, bool) const { return operand->eval(scope, true); }
    virtual bool equals(const AbstractExpression *other) const;
    virtual std::string toString() const { return "lazy(" + operand->toString() + ")"; }
};

}

#endif // LAZYEVAL_H
