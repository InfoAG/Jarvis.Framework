#include "AbstractLevelingExpression.h"

namespace CAS {

AbstractLevelingExpression::AbstractLevelingExpression(ExpressionP first_op, ExpressionP second_op)
{
    operands.emplace_back(std::move(first_op));
    operands.emplace_back(std::move(second_op));
}

AbstractLevelingExpression::AbstractLevelingExpression(const AbstractLevelingExpression &other)
{
    operands.reserve(other.operands.size());
    for (const auto &op : other.operands)
        operands.emplace_back(op->copyEx());
}

AbstractExpression::ExpressionP AbstractLevelingExpression::substituteConstants() const
{
    Expressions resOps;
    for (const auto &op : operands) resOps.emplace_back(op->substituteConstants());
    return constructWithArgs(std::move(resOps));
}

bool AbstractLevelingExpression::hasVar(const std::string &id) const
{
    for (const auto &op : operands) if (op->hasVar(id)) return true;
    return false;
}

bool AbstractLevelingExpression::isSymbolic(Scope &scope) const
{
    for (const auto &op : operands) if (op->isSymbolic(scope)) return true;
    return false;
}

}
