#ifndef LAZYEVAL_H
#define LAZYEVAL_H

#include "AbstractUnaryOperation.h"

namespace CAS {

class LazyEval : public AbstractUnaryOperation
{
public:
    LazyEval(std::unique_ptr<AbstractArithmetic> operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<LazyEval>(*this); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &) const { return operand->eval(EvalInfo()); }
    virtual ArithmeticType type() const { return LAZYEVAL; }
    virtual bool equals(const AbstractArithmetic *other) const;
    virtual std::string toString() const { return "lazy(" + operand->toString() + ")"; }
};

}

#endif // LAZYEVAL_H
