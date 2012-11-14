#include "List.h"

namespace CAS {

AbstractExpression::EvalRes List::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    Operands result;
    auto firstOpRes = operands.front()->eval(scope, load, lazy, direct);
    result.emplace_back(std::move(firstOpRes.second));
    for (auto it = operands.cbegin() + 1; it != operands.cend(); ++it) {
        auto opRes = (*it)->eval(scope, load, lazy, direct);
        if (opRes.first != firstOpRes.first) throw "list type inconsistency";
        result.emplace_back(std::move(opRes.second));
    }
    //if (result.size() == 1) return std::move(result.front());
    return std::make_pair(TypeInfo{TypeInfo::LIST, firstOpRes.first}, make_unique<List>(std::move(result)));
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

}
