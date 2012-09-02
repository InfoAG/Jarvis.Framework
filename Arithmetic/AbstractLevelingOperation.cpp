#include "AbstractLevelingOperation.h"

namespace CAS {

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
