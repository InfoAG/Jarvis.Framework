#ifndef LAZYEVAL_H
#define LAZYEVAL_H

#include "AbstractUnaryOperation.h"
#include "exception/ExecutionException.h"

namespace CAS {

class LazyEval : public AbstractUnaryOperation
{
public:
    LazyEval(ExpressionP operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual ExpressionP copy() const { return make_unique<LazyEval>(*this); }

    virtual ExpressionP execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const { if (execOption == EAGER) throw ExecutionException::failedEager(toString()); else return operand->execute(scope, load, LAZY); }
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual bool equals(const AbstractExpression *other) const;
    virtual std::string toString() const { return "lazy(" + operand->toString() + ")"; }
};

}

#endif // LAZYEVAL_H
