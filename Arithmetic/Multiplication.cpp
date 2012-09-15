#include "Multiplication.h"

namespace CAS {

void Multiplication::addToBasisValue(BasisValues &values, std::unique_ptr<AbstractArithmetic> basis, std::unique_ptr<AbstractArithmetic> exponent) const
{
    BasisValues::iterator it = std::find_if(begin(values), end(values),
            [&](const std::pair<std::unique_ptr<AbstractArithmetic>, std::unique_ptr<AbstractArithmetic>> &item) {
                return item.first->equals(basis.get());
        });
    if (it != values.end()) it->second = make_unique<Addition>(std::move(it->second), std::move(exponent));
    else values.emplace_back(std::move(basis), std::move(exponent));
}

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
    Natural numberValue = 1;
    BasisValues basisValues;

    // http://www.iaeng.org/publication/WCE2010/WCE2010_pp1829-1833.pdf

    for (auto &operand : mergedOperands) {
        switch (operand->type()) {
        case NUMBERARITH:
            numberValue *= static_cast<NumberArith*>(operand.get())->getValue();
            break;
        case EXPONENTIATION:
            addToBasisValue(basisValues, std::move(static_cast<Exponentiation*>(operand.get())->getFirstOp()), std::move(static_cast<Exponentiation*>(operand.get())->getSecondOp()));
            break;
        default:
            addToBasisValue(basisValues, std::move(operand), make_unique<NumberArith>(1));
        }
    }
    mergedOperands.clear();
    for (auto &basisValue : basisValues)
        mergedOperands.emplace_back(Exponentiation(std::move(basisValue.first), std::move(basisValue.second)).eval(ei));
    if (numberValue == 0 || mergedOperands.empty()) return make_unique<NumberArith>(numberValue);
    else {
        if (! (numberValue == 1)) mergedOperands.emplace_back(make_unique<NumberArith>(numberValue));
        else if (mergedOperands.size() == 1) return std::unique_ptr<AbstractArithmetic>(mergedOperands.front().release());
        return make_unique<Multiplication>(std::move(mergedOperands));
    }
}

std::string Multiplication::toString() const
{
    std::string result;
    for (auto it = operands.cbegin(); it != operands.cend(); ++it) {
        if ((*it)->type() == SUBTRACTION || (*it)->type() == ADDITION) result += "(" + (*it)->toString() + ")";
        else result += (*it)->toString();
        if (it != operands.cend() - 1) result += "*";
    }
    return result;
}

bool Multiplication::equals(const AbstractArithmetic *other) const
{
    if (other->type() != MULTIPLICATION) return false;
    return equalOperands(static_cast<const Multiplication*>(other)->getOperands(), operands);
}

}
