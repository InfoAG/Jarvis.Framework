#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "AbstractLevelingOperation.h"
#include "NumberArith.h"

namespace CAS {

class Multiplication : public AbstractLevelingOperation
{
public:
    Multiplication(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : AbstractLevelingOperation(std::move(first_op), std::move(second_op)) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return std::unique_ptr<AbstractArithmetic>(new Multiplication(*this)); }
    Multiplication(const std::vector<std::shared_ptr<AbstractArithmetic> > &operands) : AbstractLevelingOperation(operands) {}

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType getType() const { return MULTIPLICATION; }
    virtual std::string toString() const;
    virtual bool isEqual(const AbstractArithmetic *other) const;
};

}

#endif //MULTIPLICATION_H
