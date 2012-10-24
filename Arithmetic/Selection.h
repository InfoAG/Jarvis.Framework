#ifndef SELECTION_H
#define SELECTION_H

#include "AbstractLevelingOperation.h"
#include "NumberArith.h"
#include "List.h"

namespace CAS {

class Selection : public AbstractLevelingOperation
{
private:
    ExpressionP operand;

public:
    Selection(ExpressionP operand, Operands operands) : AbstractLevelingOperation(std::move(operands)), operand(std::move(operand)) {}
    Selection(const Selection &other) : AbstractLevelingOperation(other), operand(other.operand->copy()) {}

    virtual ExpressionP copy() const { return make_unique<Selection>(*this); }
    virtual EvalRes eval(Scope &scope, bool lazy) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;

    const ExpressionP &getOperand() const { return operand; }
};

}

#endif // SELECTION_H
