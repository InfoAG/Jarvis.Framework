#include "MultiLineExpression.h"

namespace CAS {

AbstractExpression::ExpressionP MultiLineExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    Operands result;
    for (const auto &op : operands) {
        auto evalRes = op->eval(scope, load, lazy, direct);
        if (typeid(*(evalRes)) == typeid(OutputExpression)) result.emplace_back(std::move(evalRes));
        else if (typeid(*(evalRes)) == typeid(ReturnExpression)) return std::move(static_cast<ReturnExpression*>(evalRes.get())->getOperand());
    }
    return make_unique<MultiLineExpression>(std::move(result));
}

TypeInfo MultiLineExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (! candidates.contains(TypeInfo::VOID)) throw "typing";
    for (const auto &op : operands)
        op->typeCheck(TypeCollection::all(), scope);
    return TypeInfo::VOID;
}

std::string MultiLineExpression::toString() const
{
    if (operands.empty()) return std::string();
    std::string result;
    for (auto it = operands.cbegin(); it != operands.cend(); ++it) {
        result += (*it)->toString();
        if (typeid(**it) != typeid(OutputExpression)) result += ";";
        if (it != operands.cend() - 1) result += "\n";
    }
    return result;
}

bool MultiLineExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(MultiLineExpression) && equalOperands(operands, static_cast<const MultiLineExpression*>(other)->getOperands());
}

}
