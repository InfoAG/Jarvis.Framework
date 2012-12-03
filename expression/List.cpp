#include "List.h"

namespace CAS {

AbstractExpression::ExpressionP List::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    Operands result;
    for (const auto &op : operands) result.emplace_back(op->eval(scope, load, lazy, direct));
    //if (result.size() == 1) return std::move(result.front());
    return make_unique<List>(std::move(result));
}

TypeInfo List::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    TypeCollection elementTs{candidates.flattenToElements()};
    TypeInfo elT;
    Operands::const_iterator it;
    for (it = operands.cbegin(); it != operands.cend(); ++it) {
        try {
            elT = (*it)->typeCheck(elementTs, scope);
            break;
        } catch (const char *) {}
    }
    if (it == operands.cend()) throw "typing";
    for (auto oIt = operands.cbegin(); oIt != operands.cend(); ++oIt)
        if (it != oIt) (*oIt)->typeCheck({{elT}}, scope);
    return TypeInfo(TypeInfo::LIST, {elT});
}

std::string List::toString() const
{
    std::string result = "[";
    if (typeid(operands.front()) == typeid(List))
        for (const auto &operand : operands) result += operand->toString();
    else {
        for (auto it = operands.cbegin(); it != operands.cend() - 1; ++it)
            result += (*it)->toString() + ",";
        result += operands.back()->toString();
    }
    return result + "]";
}

bool List::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(List) && equalOperands(operands, static_cast<const List*>(other)->getOperands());
}

List List::operator/(const List &other) const
{
    if (operands.size() != other.operands.size())
        throw "List/List dim mismatch";
    Operands result;
    auto itOther = other.operands.cbegin();
    for (const auto &op : operands) {
        result.emplace_back(make_unique<Division>(op->copy(), (*itOther)->copy()));
        ++itOther;
    }
    return List(std::move(result));
}

List List::operator/(const NumberValue &other) const
{
    Operands result;
    for (const auto &op : operands)
        result.emplace_back(make_unique<Division>(op->copy(), other.copy()));
    return List(std::move(result));
}

}
