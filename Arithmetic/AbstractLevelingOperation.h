#ifndef ABSTRACTLEVELINGOPERATION_H
#define ABSTRACTLEVELINGOPERATION_H

#include "AbstractArithmetic.h"

namespace CAS {

class AbstractLevelingOperation : public AbstractArithmetic
{
protected:
    Operands operands;

    template <class T>
    bool equalOperands(const T &first, const Operands &second) const
    {
        typedef std::vector<const AbstractArithmetic*> OperandRefs;
        bool deleted;
        if (second.size() == first.size()) {
            OperandRefs spareSecondOps;
            for (const auto &operand : second) spareSecondOps.emplace_back(operand.get());
            for (const auto &firstItem : first){
                deleted = false;
                for (OperandRefs::iterator secondIt = spareSecondOps.begin(); secondIt != spareSecondOps.end(); ++secondIt) {
                    if (firstItem->equals(*secondIt)) {
                        spareSecondOps.erase(secondIt);
                        deleted = true;
                        break;
                    }
                }
                if (! deleted) return false;
            }
            return true;
        } else return false;
    }

public:
    AbstractLevelingOperation(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op);
    AbstractLevelingOperation(const AbstractLevelingOperation &other);
    AbstractLevelingOperation(Operands &&operands) : operands(std::forward<Operands>(operands)) {}
    const Operands &getOperands() const { return operands; }
    Operands &getOperands() { return operands; }
};

}

#endif // ABSTRACTLEVELINGOPERATION_H
