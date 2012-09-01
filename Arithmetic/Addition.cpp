#include "Addition.h"

namespace CAS {

double &Addition::accessMonomValue(MonomValues &values, std::vector<std::unique_ptr<AbstractArithmetic>> &monom) const
{
    MonomValues::iterator it = std::find_if(begin(values), end(values),
            [&](const std::pair<Operands, double> &item) {
                return equalOperands(item.first, monom);
        });
    if (it != values.end()) return it->second;
    else {
        values.emplace_back(std::move(monom), 0);
        return values.back().second;
    }
}

std::unique_ptr<AbstractArithmetic> Addition::eval(const EvalInfo &ei) const
{
    Operands mergedOperands;
    for (const auto &operand : operands) {
        auto evalRes = operand->eval(ei);
        if (evalRes->getType() == ADDITION) {
            for (auto &childOp : static_cast<Addition*>(evalRes.get())->getOperands())
                mergedOperands.emplace_back(std::move(childOp));
        }
        else mergedOperands.emplace_back(std::move(evalRes));
    }
    MonomValues monomValues;
    double numberValue = 0;
    for (auto &operand : mergedOperands) {
        switch(operand->getType()) {
        case NUMBERARITH:
            numberValue += static_cast<NumberArith*>(operand.get())->getValue();
            break;
        case MULTIPLICATION:
            if (static_cast<Multiplication*>(operand.get())->getOperands().back()->getType() == NUMBERARITH) {
                Operands monom;
                for (auto itChild = begin(static_cast<Multiplication*>(operand.get())->getOperands());
                     itChild != end(static_cast<Multiplication*>(operand.get())->getOperands()) - 1; ++itChild)
                    monom.emplace_back(std::move(*itChild));
                accessMonomValue(monomValues, monom) +=
                        static_cast<NumberArith*>(static_cast<Multiplication*>(operand.get())->getOperands().back().get())->getValue();
            } else accessMonomValue(monomValues, static_cast<Multiplication*>(operand.get())->getOperands())++;
            break;
        default:
            Operands singleOpVec;
            singleOpVec.emplace_back(std::move(operand));
            accessMonomValue(monomValues, singleOpVec)++;
            break;
        }
    }
    mergedOperands.clear();
    if (numberValue != 0) mergedOperands.emplace_back(make_unique<NumberArith>(numberValue));
    for (auto &item : monomValues) {
        if (item.second != 0) {
            if (item.second != 1) {
                item.first.emplace_back(make_unique<NumberArith>(item.second));
                mergedOperands.emplace_back(make_unique<Multiplication>(std::move(item.first)));
            } else mergedOperands.emplace_back(make_unique<Multiplication>(std::move(item.first)));
        }
    }
    if (mergedOperands.size() == 0) return make_unique<NumberArith>(0);
    else if (mergedOperands.size() == 1) return std::move(mergedOperands.front());
    else return make_unique<Addition>(std::move(mergedOperands));
}

std::string Addition::toString() const
{
    std::string result = operands.front()->toString();
    for (auto it = ++(operands.cbegin()); it != operands.cend(); ++it)
        result += "+" + (*it)->toString();
    return result;
}

bool Addition::isEqual(const AbstractArithmetic *other) const
{
    if (other->getType() != ADDITION) return false;
    return equalOperands(static_cast<const Addition*>(other)->getOperands(), operands);
}

}
