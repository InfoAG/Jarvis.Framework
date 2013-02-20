#include "MultiLine.h"

namespace CAS {

MultiLine::MultiLine(const MultiLine &other)
{
    for (const auto &op : other.operands) operands.emplace_back(op->copy());
}

AbstractExpression::ExpressionP MultiLine::execute(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    for (const auto &op : operands) {
        auto evalRes = op->execute(scope, load, print, execOption);
        if (typeid(*(evalRes)) == typeid(ReturnExpression)) return std::move(static_cast<ReturnExpression*>(evalRes.get())->getExpression());
    }
    return make_unique<Void>();
}

TypeInfo MultiLine::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::VOID);
    for (const auto &op : operands)
        op->typeCheck(TypeCollection::all(), scope);
    return TypeInfo::VOID;
}

std::string MultiLine::toString() const
{
    if (operands.empty()) return std::string();
    std::string result;
    for (auto it = operands.cbegin(); it != operands.cend(); ++it) {
        result += (*it)->toString();
        if (typeid(**it) != typeid(Print)) result += ";";
        if (it != operands.cend() - 1) result += "\n";
    }
    return result;
}

bool MultiLine::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(MultiLine) && equalOperands(operands, static_cast<const MultiLine*>(other)->getOperands());
}

}
