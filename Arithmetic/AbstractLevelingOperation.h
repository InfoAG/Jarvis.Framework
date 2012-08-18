#ifndef ABSTRACTLEVELINGOPERATION_H
#define ABSTRACTLEVELINGOPERATION_H

#include "AbstractArithmetic.h"

namespace CAS {

class AbstractLevelingOperation : public AbstractArithmetic
{
protected:
    Operands operands;

    bool equalOperands(const Operands &first, Operands second) const;

public:
    AbstractLevelingOperation(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : operands{std::move(first_op), std::move(second_op)} {};
    //LevelingOperation(const LevelingOperation &other) : first_op(other.first_op->copy()), second_op(other.second_op->copy()) {}
    AbstractLevelingOperation(const Operands &operands) : operands(operands) {}
    Operands getOperands() const { return operands; }
};

}

#endif // ABSTRACTLEVELINGOPERATION_H
