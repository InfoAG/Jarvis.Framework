#ifndef ABSTRACTLEVELINGOPERATION_H
#define ABSTRACTLEVELINGOPERATION_H

#include "AbstractArithmetic.h"
#include <vector>

namespace CAS {

class AbstractLevelingOperation : public AbstractArithmetic
{
protected:
    std::vector<std::shared_ptr<AbstractArithmetic> > operands;

    bool equalOperands(const std::vector<std::shared_ptr<AbstractArithmetic> > &first, std::vector<std::shared_ptr<AbstractArithmetic> > second) const;

public:
    AbstractLevelingOperation(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : operands{std::move(first_op), std::move(second_op)} {};
    //LevelingOperation(const LevelingOperation &other) : first_op(other.first_op->copy()), second_op(other.second_op->copy()) {}
    AbstractLevelingOperation(const std::vector<std::shared_ptr<AbstractArithmetic> > &operands) : operands(operands) {}
    std::vector<std::shared_ptr<AbstractArithmetic> > getOperands() const { return operands; }
};

}

#endif // ABSTRACTLEVELINGOPERATION_H
