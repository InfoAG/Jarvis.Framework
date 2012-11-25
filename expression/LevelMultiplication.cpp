#include "LevelMultiplication.h"
#include "List.h"

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
    VectorExpression vec;
    std::map<unsigned int, Operands> listByDimension;

    // http://www.iaeng.org/publication/WCE2010/WCE2010_pp1829-1833.pdf


    while (! mergedOperands.empty()) {
        auto &operand = mergedOperands.front();
        if (typeid(*operand) == typeid(NumberArith))
            numberValue *= static_cast<NumberArith*>(operand.get())->getValue();
        else if (typeid(*operand) == typeid(VectorExpression))
            vec = std::move(*static_cast<VectorExpression*>(operand.get()));
        else if (typeid(*operand) == typeid(List)) {
            auto findRes = listByDimension.find(static_cast<List*>(operand.get())->getOperands().size());
            if (findRes == listByDimension.end())
                listByDimension[static_cast<List*>(operand.get())->getOperands().size()] = std::move(static_cast<List*>(operand.get())->getOperands());
            else {
                auto listIt = static_cast<List*>(operand.get())->getOperands().begin();
                for (auto &cell : findRes->second)
                    cell = make_unique<BinaryMultiplication>(std::move(cell), std::move(*listIt++));
            }
        } else if (typeid(*operand) == typeid(Exponentiation))
            addToBasisValue(basisValues, std::move(static_cast<Exponentiation*>(operand.get())->getFirstOp()), std::move(static_cast<Exponentiation*>(operand.get())->getSecondOp()));
        else
            addToBasisValue(basisValues, std::move(operand), make_unique<NumberArith>(1));
        mergedOperands.erase(begin(mergedOperands));
    }
    mergedOperands.clear();
    if (numberValue == 0) return std::make_pair(TypeInfo::NUMBER, make_unique<NumberArith>(0));
    else {
        if (numberValue == 1) {
            if (vec.getX() != nullptr)
                mergedOperands.emplace_back(make_unique<VectorExpression>(std::move(vec)));
        } else {
            if (vec.getX() != nullptr) {
                vec = *static_cast<VectorExpression*>(VectorExpression(make_unique<LevelMultiplication>(make_unique<NumberArith>(numberValue), std::move(vec.getX())), make_unique<LevelMultiplication>(make_unique<NumberArith>(numberValue), std::move(vec.getY())), make_unique<LevelMultiplication>(make_unique<NumberArith>(numberValue), std::move(vec.getZ()))).eval(scope, load, lazy, direct).second.get());
                mergedOperands.emplace_back(make_unique<VectorExpression>(std::move(vec)));
            } else if (! listByDimension.empty()) {
                for (auto &cell : listByDimension.begin()->second)
                    cell = make_unique<BinaryMultiplication>(std::move(cell), make_unique<NumberArith>(numberValue));
            } else mergedOperands.emplace_back(make_unique<NumberArith>(numberValue));
        }
        for (auto &basisValue : basisValues)
            mergedOperands.emplace_back(Exponentiation(std::move(basisValue.first), std::move(basisValue.second)).eval(scope, load, lazy, direct).second);
        for (auto &list : listByDimension)
            mergedOperands.emplace_back(List(std::move(list.second)).eval(scope, load, lazy, direct).second);
        if (mergedOperands.size() == 1) return std::make_pair(std::move(returnType), std::move(mergedOperands.front()));
        else if (mergedOperands.empty()) return std::make_pair(TypeInfo::NUMBER, make_unique<NumberArith>(1));
        else return std::make_pair(std::move(returnType), make_unique<LevelMultiplication>(std::move(mergedOperands)));
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
