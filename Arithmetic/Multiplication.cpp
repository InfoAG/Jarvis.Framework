#include "Multiplication.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Multiplication::eval(const EvalInfo &ei) const
{
    Operands mergedOperands;
    for (const auto &operand : operands) {
        auto evalRes = operand->eval(ei);
        if (evalRes->type() == MULTIPLICATION) {
            for (auto &childOp : static_cast<Multiplication*>(evalRes.get())->getOperands())
                mergedOperands.emplace_back(std::move(childOp));
        }
        else mergedOperands.emplace_back(std::move(evalRes));
    }
    double numberValue = 1;
    for (Operands::iterator it = begin(mergedOperands); it != end(mergedOperands);) {
        if ((*it)->type() == NUMBERARITH) {
            numberValue *= static_cast<NumberArith*>(it->get())->getValue();
            it = mergedOperands.erase(it);
        } else ++it;
    }
    if (numberValue == 0 || mergedOperands.empty()) return make_unique<NumberArith>(numberValue);
    else {
        if (numberValue != 1) mergedOperands.emplace_back(make_unique<NumberArith>(numberValue));
        else if (mergedOperands.size() == 1) return std::move(mergedOperands.front());
        return make_unique<Multiplication>(std::move(mergedOperands));
    }
}

std::string Multiplication::toString() const
{
    std::string result = operands.front()->toString();
    for (auto it = ++(operands.cbegin()); it != operands.cend(); ++it)
        result += "*" + (*it)->toString();
    return result;
}

bool Multiplication::equals(const AbstractArithmetic *other) const
{
    if (other->type() != MULTIPLICATION) return false;
    return equalOperands(static_cast<const Multiplication*>(other)->getOperands(), operands);
}

}
