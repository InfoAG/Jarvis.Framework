#include "Selection.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Selection::eval(const EvalInfo &ei) const
{
    std::unique_ptr<AbstractArithmetic> opResult = operand->eval(ei), firstSelectRes = operands.front()->eval(ei);

    if (opResult->type() == MATRIX && firstSelectRes->type() == NUMBERARITH && static_cast<const NumberArith*>(firstSelectRes.get())->getValue() < static_cast<const Matrix*>(opResult.get())->getOperands().size()) {
        if (operands.size() == 1)
            return std::move(static_cast<Matrix*>(opResult.get())->getOperands().at(static_cast<const NumberArith*>(firstSelectRes.get())->getValue().getDigitsAt(0)));
        else {
            Operands newOps;
            newOps.reserve(operands.size());
            for (auto it = operands.cbegin() + 1; it != operands.cend(); ++it)
                newOps.emplace_back((*it)->copy());
            return Selection(std::move(static_cast<Matrix*>(opResult.get())->getOperands().at(static_cast<const NumberArith*>(firstSelectRes.get())->getValue().getDigitsAt(0))), std::move(newOps)).eval(ei);
        }
    } else {
        Operands newOps;
        newOps.emplace_back(std::move(firstSelectRes));
        for (auto it = operands.cbegin() + 1; it != operands.cend(); ++it)
            newOps.emplace_back((*it)->eval(ei));
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

bool Selection::equals(const AbstractArithmetic *other) const
{
    return other->type() == SELECTION && operand->equals(static_cast<const Selection*>(other)->getOperand().get()) && equalOperands(operands, static_cast<const Selection*>(other)->getOperands());
}

}
