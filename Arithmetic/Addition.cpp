#include "Addition.h"

namespace CAS {

Natural &Addition::accessMonomValue(MonomValues &values, Operands monom) const
{
    MonomValues::iterator it = std::find_if(begin(values), end(values),
            [&](const std::pair<std::vector<AbstractArithmetic*>, Natural> &item) {
                return equalOperands(item.first, monom);
        });
    if (it != values.end()) return it->second;
    else {
        std::vector<AbstractArithmetic*> pairMoveWorkaround;
        for (auto &ptr : monom) pairMoveWorkaround.emplace_back(ptr.release());
        values.emplace_back(std::move(pairMoveWorkaround), 0);
        return values.back().second;
    }
}

std::unique_ptr<AbstractArithmetic> Addition::eval(const EvalInfo &ei) const
{
    Operands mergedOperands;
    mergedOperands.reserve(operands.size());
    for (const auto &operand : operands) {
        auto evalRes = operand->eval(ei);
        if (evalRes->type() == ADDITION) {
            for (auto &childOp : static_cast<Addition*>(evalRes.get())->getOperands())
                mergedOperands.emplace_back(std::move(childOp));
        }
        else mergedOperands.emplace_back(std::move(evalRes));
    }
    MonomValues monomValues;
    Natural numberValue = 0;
    std::map<unsigned int, Operands> matrixByDimension;
    for (auto &operand : mergedOperands) {
        switch (operand->type()) {
        case NUMBERARITH:
            numberValue += static_cast<NumberArith*>(operand.get())->getValue();
            break;
        case MULTIPLICATION:
            if (static_cast<Multiplication*>(operand.get())->getOperands().back()->type() == NUMBERARITH) {
                /*Operands monom;
                for (auto itChild = begin(static_cast<Multiplication*>(operand.get())->getOperands());
                     itChild != end(static_cast<Multiplication*>(operand.get())->getOperands()) - 1; ++itChild)
                    monom.emplace_back(std::move(*itChild));*/
                Natural monomValue = std::move(static_cast<NumberArith*>(static_cast<Multiplication*>(operand.get())->getOperands().back().get())->getValue());
                static_cast<Multiplication*>(operand.get())->getOperands().erase(end(static_cast<Multiplication*>(operand.get())->getOperands()));
                accessMonomValue(monomValues, std::move(static_cast<Multiplication*>(operand.get())->getOperands())) += monomValue;
            } else accessMonomValue(monomValues, std::move(static_cast<Multiplication*>(operand.get())->getOperands()))++;
            break;
        case MATRIX: {
                auto findRes = matrixByDimension.find(static_cast<Matrix*>(operand.get())->getOperands().size());
                if (findRes == matrixByDimension.end())
                    matrixByDimension[static_cast<Matrix*>(operand.get())->getOperands().size()] = std::move(static_cast<Matrix*>(operand.get())->getOperands());
                else {
                    auto matrixIt = static_cast<Matrix*>(operand.get())->getOperands().begin();
                    for (auto &cell : findRes->second)
                        cell = make_unique<Addition>(std::move(cell), std::move(*matrixIt++));
                }
            }
            break;
        default:
            Operands singleOpVec(1);
            singleOpVec.at(0) = std::move(operand);
            accessMonomValue(monomValues, std::move(singleOpVec))++;
            break;
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
    for (auto &matrix : matrixByDimension) mergedOperands.emplace_back(Matrix(std::move(matrix.second)).eval(ei));
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
        if ((*it)->type() == SUBTRACTION) result += "(" + (*it)->toString() + ")";
        else result += (*it)->toString();
        if (it != operands.cend() - 1) result += "+";
    }
    return result;
}

bool Addition::equals(const AbstractArithmetic *other) const
{
    if (other->type() != ADDITION) return false;
    return equalOperands(static_cast<const Addition*>(other)->getOperands(), operands);
}

}
