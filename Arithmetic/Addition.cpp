#include "Addition.h"

namespace CAS {

Integer &Addition::accessMonomValue(MonomValues &values, Operands monom) const
{
    MonomValues::iterator it = std::find_if(begin(values), end(values),
            [&](const std::pair<std::vector<AbstractExpression*>, Integer> &item) {
                return equalOperands(item.first, monom);
        });
    if (it != values.end()) return it->second;
    else {
        std::vector<AbstractExpression*> pairMoveWorkaround;
        for (auto &ptr : monom) pairMoveWorkaround.emplace_back(ptr.release());
        values.emplace_back(std::move(pairMoveWorkaround), 0);
        return values.back().second;
    }
}

std::unique_ptr<AbstractExpression> Addition::eval(Scope &scope, bool lazy) const
{
    Operands mergedOperands;
    mergedOperands.reserve(operands.size());
    for (const auto &operand : operands) {
        auto evalRes = operand->eval(scope, lazy);
        if (typeid(evalRes) == typeid(Addition)) {
            for (auto &childOp : static_cast<Addition*>(evalRes.get())->getOperands())
                mergedOperands.emplace_back(std::move(childOp));
        }
        else mergedOperands.emplace_back(std::move(evalRes));
    }
    MonomValues monomValues;
    Integer numberValue = 0;
    std::map<unsigned int, Operands> matrixByDimension;
    for (auto &operand : mergedOperands) {
        if (typeid(*operand) == typeid(NumberArith))
            numberValue += static_cast<NumberArith*>(operand.get())->getValue();
        else if (typeid(*operand) == typeid(Multiplication)) {
            if (typeid(static_cast<Multiplication*>(operand.get())->getOperands().back()) == typeid(NumberArith)) {
                /*Operands monom;
                for (auto itChild = begin(static_cast<Multiplication*>(operand.get())->getOperands());
                     itChild != end(static_cast<Multiplication*>(operand.get())->getOperands()) - 1; ++itChild)
                    monom.emplace_back(std::move(*itChild));*/
                Integer monomValue = std::move(static_cast<NumberArith*>(static_cast<Multiplication*>(operand.get())->getOperands().back().get())->getValue());
                static_cast<Multiplication*>(operand.get())->getOperands().erase(end(static_cast<Multiplication*>(operand.get())->getOperands()));
                accessMonomValue(monomValues, std::move(static_cast<Multiplication*>(operand.get())->getOperands())) += monomValue;
            } else accessMonomValue(monomValues, std::move(static_cast<Multiplication*>(operand.get())->getOperands()))++;
        } else if (typeid(*operand) == typeid(Matrix)) {
                auto findRes = matrixByDimension.find(static_cast<Matrix*>(operand.get())->getOperands().size());
                if (findRes == matrixByDimension.end())
                    matrixByDimension[static_cast<Matrix*>(operand.get())->getOperands().size()] = std::move(static_cast<Matrix*>(operand.get())->getOperands());
                else {
                    auto matrixIt = static_cast<Matrix*>(operand.get())->getOperands().begin();
                    for (auto &cell : findRes->second)
                        cell = make_unique<Addition>(std::move(cell), std::move(*matrixIt++));
                }
        } else {
            Operands singleOpVec(1);
            singleOpVec.at(0) = std::move(operand);
            accessMonomValue(monomValues, std::move(singleOpVec))++;
        }
    }
    mergedOperands.clear();
    if (numberValue != 0) {
        if (matrixByDimension.empty()) mergedOperands.emplace_back(make_unique<NumberArith>(numberValue));
        else {
            for (auto &cell : matrixByDimension.begin()->second)
                cell = make_unique<Addition>(std::move(cell), make_unique<NumberArith>(numberValue));
        }
    }
    for (auto &matrix : matrixByDimension) mergedOperands.emplace_back(Matrix(std::move(matrix.second)).eval(scope, lazy));
    for (auto &item : monomValues) {
        Operands workaroundVec;
        for (const auto &monomItem : item.first) workaroundVec.emplace_back(monomItem);
        if (item.second != 0) {
            if (item.second != 1) {
                workaroundVec.emplace_back(make_unique<NumberArith>(item.second));
                mergedOperands.emplace_back(make_unique<Multiplication>(std::move(workaroundVec)));
            } else mergedOperands.emplace_back(make_unique<Multiplication>(std::move(workaroundVec)));
        }
    }
    if (mergedOperands.size() == 0) return make_unique<NumberArith>(0);
    else if (mergedOperands.size() == 1) return std::move(mergedOperands.front());
    else return make_unique<Addition>(std::move(mergedOperands));
}

std::string Addition::toString() const
{
    std::string result;
    for (auto it = operands.cbegin(); it != operands.cend(); ++it) {
        if (typeid(*it) == typeid(Subtraction)) result += "(" + (*it)->toString() + ")";
        else result += (*it)->toString();
        if (it != operands.cend() - 1) result += "+";
    }
    return result;
}

bool Addition::equals(const AbstractExpression *other) const
{
    if (typeid(*other) != typeid(Addition)) return false;
    return equalOperands(static_cast<const Addition*>(other)->getOperands(), operands);
}

}
