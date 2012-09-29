#ifndef SELECTION_H
#define SELECTION_H

#include "AbstractLevelingOperation.h"
#include "NumberArith.h"
#include "Matrix.h"

namespace CAS {

class Selection : public AbstractLevelingOperation
{
private:
    std::unique_ptr<AbstractExpression> operand;

public:
    Selection(std::unique_ptr<AbstractExpression> operand, Operands operands) : AbstractLevelingOperation(std::move(operands)), operand(std::move(operand)) {}
    Selection(const Selection &other) : AbstractLevelingOperation(other), operand(other.operand->copy()) {}

    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<Selection>(*this); }
    virtual std::unique_ptr<AbstractExpression> eval(Scope &scope, bool lazy) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;

    const std::unique_ptr<AbstractExpression> &getOperand() const { return operand; }
};

}

#endif // SELECTION_H
