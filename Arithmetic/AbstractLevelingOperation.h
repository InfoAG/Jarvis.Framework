#ifndef ABSTRACTLEVELINGOPERATION_H
#define ABSTRACTLEVELINGOPERATION_H

#include "AbstractArithmetic.h"

namespace CAS {

class AbstractLevelingOperation : public AbstractArithmetic
{
protected:
    Operands operands;

    bool equalOperands(const Operands &first, const Operands &second) const;

public:
    AbstractLevelingOperation(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op);
    AbstractLevelingOperation(const AbstractLevelingOperation &other);
    AbstractLevelingOperation(Operands &&operands) : operands(std::forward<Operands>(operands)) {}
    const Operands &getOperands() const { return operands; }
    Operands &getOperands() { return operands; }
};

}

#endif // ABSTRACTLEVELINGOPERATION_H
