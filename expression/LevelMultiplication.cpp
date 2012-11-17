#include "LevelMultiplication.h"

namespace CAS {

void LevelMultiplication::addToBasisValue(BasisValues &values, ExpressionP basis, ExpressionP exponent) const
{
    BasisValues::iterator it = std::find_if(begin(values), end(values),
            [&](const std::pair<ExpressionP, ExpressionP> &item) {
                return item.first->equals(basis.get());
        });
    if (it != values.end()) it->second = make_unique<Addition>(std::move(it->second), std::move(exponent));
    else values.emplace_back(std::move(basis), std::move(exponent));
}

AbstractExpression::EvalRes LevelMultiplication::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    Operands mergedOperands;
    TypeInfo returnType = TypeInfo::NUMBER;
    for (const auto &operand : operands) {
        auto evalRes = operand->eval(scope, load, lazy, direct);
        if (typeid(*(evalRes.second)) == typeid(LevelMultiplication)) {
            for (auto &childOp : static_cast<LevelMultiplication*>(evalRes.second.get())->getOperands())
                mergedOperands.emplace_back(std::move(childOp));
        }
        else mergedOperands.emplace_back(std::move(evalRes.second));
        if (evalRes.first != TypeInfo::NUMBER) returnType = evalRes.first;
    }
    double numberValue = 1;
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
        mergedOperands.emplace_back(Exponentiation(std::move(basisValue.first), std::move(basisValue.second)).eval(scope, load, lazy, direct).second);
    if (numberValue == 0 || mergedOperands.empty()) return std::make_pair(TypeInfo{TypeInfo::NUMBER}, make_unique<NumberArith>(numberValue));
    else {
        if (! (numberValue == 1)) mergedOperands.emplace_back(make_unique<NumberArith>(numberValue));
        else if (mergedOperands.size() == 1) return std::make_pair(returnType, std::move(mergedOperands.front()));
        return std::make_pair(returnType, make_unique<LevelMultiplication>(std::move(mergedOperands)));
    }
}

std::string LevelMultiplication::toString() const
{
    std::string result;
    for (auto it = operands.cbegin(); it != operands.cend(); ++it) {
        if (typeid(*it) == typeid(Subtraction) || typeid(*it) == typeid(Addition)) result += "(" + (*it)->toString() + ")";
        else result += (*it)->toString();
        if (it != operands.cend() - 1) result += "*";
    }
    return result;
}

bool LevelMultiplication::equals(const AbstractExpression *other) const
{
    if (typeid(*other) != typeid(LevelMultiplication)) return false;
    return equalOperands(static_cast<const LevelMultiplication*>(other)->getOperands(), operands);
}

}
