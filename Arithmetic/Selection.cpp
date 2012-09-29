#include "Selection.h"

namespace CAS {

std::unique_ptr<AbstractExpression> Selection::eval(Scope &scope, bool lazy) const
{
    std::unique_ptr<AbstractExpression> opResult = operand->eval(scope, lazy), firstSelectRes = operands.front()->eval(scope, lazy);

    if (typeid(opResult) == typeid(Matrix) && typeid(firstSelectRes) == typeid(NumberArith) && static_cast<const NumberArith*>(firstSelectRes.get())->getValue() < static_cast<const Matrix*>(opResult.get())->getOperands().size()) {
        if (operands.size() == 1)
            return std::move(static_cast<Matrix*>(opResult.get())->getOperands().at(static_cast<const NumberArith*>(firstSelectRes.get())->getValue().getNumberAt(0)));
        else {
            Operands newOps;
            newOps.reserve(operands.size());
            for (auto it = operands.cbegin() + 1; it != operands.cend(); ++it)
                newOps.emplace_back((*it)->copy());
            return Selection(std::move(static_cast<Matrix*>(opResult.get())->getOperands().at(static_cast<const NumberArith*>(firstSelectRes.get())->getValue().getNumberAt(0))), std::move(newOps)).eval(scope, lazy);
        }
    } else {
        Operands newOps;
        newOps.emplace_back(std::move(firstSelectRes));
        for (auto it = operands.cbegin() + 1; it != operands.cend(); ++it)
            newOps.emplace_back((*it)->eval(scope, lazy));
        return make_unique<Selection>(std::move(opResult), std::move(newOps));
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
