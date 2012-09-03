#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "AbstractLevelingOperation.h"
#include "NumberArith.h"

namespace CAS {

class Multiplication : public AbstractLevelingOperation
{
public:
    Multiplication(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : AbstractLevelingOperation(std::move(first_op), std::move(second_op)) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<Multiplication>(*this); }
    Multiplication(Operands &&operands) : AbstractLevelingOperation(std::forward<Operands>(operands)) {}

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType type() const { return MULTIPLICATION; }
    virtual std::string toString() const;
    virtual bool equals(const AbstractArithmetic *other) const;
};

}

#endif //MULTIPLICATION_H
