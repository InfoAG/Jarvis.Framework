#include "Addition.h"

namespace CAS {

int &Addition::accessMonomValue(MonomValues &values, const std::vector<std::shared_ptr<AbstractArithmetic> > &monom) const
{
    std::vector<std::pair<std::vector<std::shared_ptr<AbstractArithmetic> >, int> >::iterator it = std::find_if(begin(values), end(values),
            [&](const std::pair<std::vector<std::shared_ptr<AbstractArithmetic> >, int> &item) {
                return equalOperands(item.first, monom);
        });
    if (it != values.end()) return it->second;
    else {
        values.push_back(std::make_pair(monom, 0));
        return values.back().second;
    }
}

std::unique_ptr<AbstractArithmetic> Addition::eval(const EvalInfo &ei) const
{
    std::vector<std::shared_ptr<AbstractArithmetic> > mergedOperands;
    for (const auto &operand : operands) {
        std::shared_ptr<AbstractArithmetic> evalRes = operand->eval(ei);
        if (evalRes->getType() == AbstractArithmetic::ADDITION) {
            std::vector<std::shared_ptr<AbstractArithmetic> > childOperands = static_cast<Addition*>(evalRes.get())->getOperands();
            mergedOperands.insert(begin(mergedOperands), begin(childOperands), end(childOperands));
        }
        else mergedOperands.push_back(evalRes);
    }
    MonomValues monomValues;
    int numberValue = 0;
    std::vector<std::shared_ptr<AbstractArithmetic> > monomOperands;
    for (const auto &operand : mergedOperands) {
        switch(operand->getType()) {
        case AbstractArithmetic::NUMBERARITH:
            numberValue += static_cast<NumberArith*>(operand.get())->getValue();
            break;
        case AbstractArithmetic::MULTIPLICATION:
            monomOperands = static_cast<Multiplication*>(operand.get())->getOperands();
            if (monomOperands.back()->getType() == AbstractArithmetic::NUMBERARITH) {
                accessMonomValue(monomValues, {begin(monomOperands), end(monomOperands) - 1}) += static_cast<NumberArith*>(monomOperands.back().get())->getValue();
            } else accessMonomValue(monomValues, monomOperands)++;
            break;
        default:
            accessMonomValue(monomValues, {operand})++;
            break;
        }
    }
    mergedOperands.clear();
    if (numberValue != 0) mergedOperands.push_back(std::make_shared<NumberArith>(numberValue));
    for (const auto &item : monomValues) {
        if (item.second != 0) {
            if (item.second != 1) {
                std::vector<std::shared_ptr<AbstractArithmetic> > resultMultiplication(item.first);
                resultMultiplication.push_back(std::make_shared<NumberArith>(item.second));
                mergedOperands.push_back(std::make_shared<Multiplication>(resultMultiplication));
            } else mergedOperands.push_back(std::make_shared<Multiplication>(item.first));
        }
    }
    return std::unique_ptr<AbstractArithmetic>(new Addition(mergedOperands));
}

std::string Addition::toString() const
{
    std::string result = operands.front()->toString();
    for (std::vector<std::shared_ptr<AbstractArithmetic> >::const_iterator it = ++(operands.begin()); it != operands.end(); ++it)
        result += "+" + (*it)->toString();
    return result;
}

bool Addition::isEqual(const AbstractArithmetic *other) const
{
    if (other->getType() != AbstractArithmetic::ADDITION) return false;
    return equalOperands(static_cast<const Addition*>(other)->getOperands(), operands);
}

}
