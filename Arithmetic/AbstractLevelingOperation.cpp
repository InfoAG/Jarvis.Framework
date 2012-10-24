#include "AbstractLevelingOperation.h"

namespace CAS {

AbstractLevelingOperation::AbstractLevelingOperation(ExpressionP first_op, ExpressionP second_op)
{
    operands.emplace_back(std::move(first_op));
    operands.emplace_back(std::move(second_op));
}

AbstractLevelingOperation::AbstractLevelingOperation(const AbstractLevelingOperation &other)
{
    operands.reserve(other.operands.size());
    for (const auto &op : other.operands)
        operands.emplace_back(op->copy());
}

}
