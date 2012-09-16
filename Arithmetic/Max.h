#ifndef MAX_H
#define MAX_H

#include "AbstractBinaryOperation.h"
#include "NumberArith.h"

namespace CAS {

class Max : public AbstractBinaryOperation
{
public:
    Max(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<Max>(*this); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType type() const { return MAX; }
    virtual bool equals(const AbstractArithmetic *other) const;
    virtual std::string toString() const { return "max(" + first_op->toString() + "," + second_op->toString() + ")"; }
};

}

#endif // MAX_H
