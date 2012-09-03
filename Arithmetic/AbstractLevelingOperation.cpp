#include "AbstractLevelingOperation.h"

namespace CAS {

bool AbstractLevelingOperation::equalOperands(const Operands &first, const Operands &second) const
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

AbstractLevelingOperation::AbstractLevelingOperation(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op)
{
    operands.emplace_back(std::move(first_op));
    operands.emplace_back(std::move(second_op));
}

AbstractLevelingOperation::AbstractLevelingOperation(const AbstractLevelingOperation &other)
{
    for (const auto &op : other.operands)
        operands.emplace_back(op->copy());
}

}
