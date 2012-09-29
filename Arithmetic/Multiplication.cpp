#include "Multiplication.h"

namespace CAS {

void Multiplication::addToBasisValue(BasisValues &values, std::unique_ptr<AbstractExpression> basis, std::unique_ptr<AbstractExpression> exponent) const
{
    BasisValues::iterator it = std::find_if(begin(values), end(values),
            [&](const std::pair<std::unique_ptr<AbstractExpression>, std::unique_ptr<AbstractExpression>> &item) {
                return item.first->equals(basis.get());
        });
    if (it != values.end()) it->second = make_unique<Addition>(std::move(it->second), std::move(exponent));
    else values.emplace_back(std::move(basis), std::move(exponent));
}

std::unique_ptr<AbstractExpression> Multiplication::eval(Scope &scope, bool lazy) const
{
    Operands mergedOperands;
    for (const auto &operand : operands) {
        auto evalRes = operand->eval(scope, lazy);
        if (typeid(evalRes) == typeid(Multiplication)) {
            for (auto &childOp : static_cast<Multiplication*>(evalRes.get())->getOperands())
                mergedOperands.emplace_back(std::move(childOp));
        }
        else mergedOperands.emplace_back(std::move(evalRes));
    }
    Integer numberValue = 1;
    BasisValues basisValues;

    // http://www.iaeng.org/publication/WCE2010/WCE2010_pp1829-1833.pdf

    for (auto &operand : mergedOperands) {
        if (typeid(*operand) == typeid(NumberArith))
            numberValue *= static_cast<NumberArith*>(operand.get())->getValue();
        else if (typeid(*operand) == typeid(Exponentiation))
            addToBasisValue(basisValues, std::move(static_cast<Exponentiation*>(operand.get())->getFirstOp()), std::move(static_cast<Exponentiation*>(operand.get())->getSecondOp()));
        else
            addToBasisValue(basisValues, std::move(operand), make_unique<NumberArith>(1));
    }
    mergedOperands.clear();
    for (auto &basisValue : basisValues)
        mergedOperands.emplace_back(Exponentiation(std::move(basisValue.first), std::move(basisValue.second)).eval(scope, lazy));
    if (numberValue == 0 || mergedOperands.empty()) return make_unique<NumberArith>(numberValue);
    else {
        if (! (numberValue == 1)) mergedOperands.emplace_back(make_unique<NumberArith>(numberValue));
        else if (mergedOperands.size() == 1) return std::unique_ptr<AbstractExpression>(mergedOperands.front().release());
        return make_unique<Multiplication>(std::move(mergedOperands));
    }
}

std::string Multiplication::toString() const
{
    std::string result;
    for (auto it = operands.cbegin(); it != operands.cend(); ++it) {
        if (typeid(*it) == typeid(Subtraction) || typeid(*it) == typeid(Addition)) result += "(" + (*it)->toString() + ")";
        else result += (*it)->toString();
        if (it != operands.cend() - 1) result += "*";
    }
    return result;
}

bool Multiplication::equals(const AbstractExpression *other) const
{
    if (typeid(*other) != typeid(Multiplication)) return false;
    return equalOperands(static_cast<const Multiplication*>(other)->getOperands(), operands);
}

}
