#ifndef SELECTION_H
#define SELECTION_H

#include "AbstractLevelingOperation.h"
#include "NumberArith.h"
#include "Matrix.h"

namespace CAS {

class Selection : public AbstractLevelingOperation
{
private:
    std::unique_ptr<AbstractArithmetic> operand;

public:
    Selection(std::unique_ptr<AbstractArithmetic> operand, Operands operands) : AbstractLevelingOperation(std::move(operands)), operand(std::move(operand)) {}
    Selection(const Selection &other) : AbstractLevelingOperation(other), operand(other.operand->copy()) {}

    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<Selection>(*this); }
    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType type() const { return SELECTION; }
    virtual std::string toString() const;
    virtual bool equals(const AbstractArithmetic *other) const;

    const std::unique_ptr<AbstractArithmetic> &getOperand() const { return operand; }
};

}

#endif // SELECTION_H
