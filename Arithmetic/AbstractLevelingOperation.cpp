#include "AbstractLevelingOperation.h"

namespace CAS {

bool AbstractLevelingOperation::equalOperands(const Operands &first, Operands second) const
{
    bool deleted;
    if (second.size() == first.size()) {
        for (const auto &firstItem : first){
            deleted = false;
            for (Operands::iterator secondIt = second.begin(); secondIt != second.end(); ++secondIt) {
                if (firstItem->isEqual(secondIt->get())) {
                    second.erase(secondIt);
                    deleted = true;
                    break;
                }
            }
            if (! deleted) return false;
        }
        return true;
    } else return false;
}

}
