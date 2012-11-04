#include "Selection.h"

namespace CAS {

AbstractExpression::EvalRes Selection::eval(Scope &scope, bool lazy) const
{
    auto opResult = operand->eval(scope, lazy), firstSelectRes = operands.front()->eval(scope, lazy);

    if (typeid(*(opResult.second)) == typeid(List) && typeid(*(firstSelectRes.second)) == typeid(NumberArith) && static_cast<const NumberArith*>(firstSelectRes.second.get())->getValue() < static_cast<const List*>(opResult.second.get())->getOperands().size()) {
        if (operands.size() == 1)
            return static_cast<List*>(opResult.second.get())->getOperands().at(static_cast<const NumberArith*>(firstSelectRes.second.get())->getValue().getNumberAt(0))->eval(scope, lazy);
        else {
            Operands newOps;
            newOps.reserve(operands.size());
            for (auto it = operands.cbegin() + 1; it != operands.cend(); ++it)
                newOps.emplace_back((*it)->copy());
            return Selection(std::move(static_cast<List*>(opResult.second.get())->getOperands().at(static_cast<const NumberArith*>(firstSelectRes.second.get())->getValue().getNumberAt(0))), std::move(newOps)).eval(scope, lazy);
        }
    } else {
        Operands newOps;
        newOps.emplace_back(std::move(firstSelectRes.second));
        for (auto it = operands.cbegin() + 1; it != operands.cend(); ++it)
            newOps.emplace_back((*it)->eval(scope, lazy).second);
        return std::make_pair(TypeInfo::VOID, make_unique<Selection>(std::move(opResult.second), std::move(newOps))); //unless all elements in list have same type
    }
}

std::string Selection::toString() const
{
    std::string result = operand->toString() + "{";
    for (auto it = operands.cbegin(); it != operands.cend() - 1; ++it)
        result += (*it)->toString() + ",";
    return result + operands.back()->toString() + "}";
}

bool Selection::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(Selection) && operand->equals(static_cast<const Selection*>(other)->getOperand().get()) && equalOperands(operands, static_cast<const Selection*>(other)->getOperands());
}

}
