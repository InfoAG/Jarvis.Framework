#ifndef LAZYEVAL_H
#define LAZYEVAL_H

#include "AbstractUnaryExpression.h"
#include "exception/ExecutionException.h"

namespace CAS {

class LazyEval : public AbstractUnaryExpression
{
public:
    LazyEval(ExpressionP operand) : AbstractUnaryExpression(std::move(operand)) {}
    virtual StatementP copy() const { return make_unique<LazyEval>(*this); }
    virtual ExpressionP constructWithArgs(ExpressionP op) const { return make_unique<LazyEval>(std::move(op)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const { if (execOption == EAGER) throw ExecutionException::failedEager(toString()); else return operand->executeExpression(scope, load, print, LAZY); }
    virtual ExpressionP substituteConstants() const { return copyEx(); }
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual bool equals(const AbstractStatement *other) const;
    virtual std::string toString() const { return "lazy(" + operand->toString() + ")"; }
};

}

#endif // LAZYEVAL_H
