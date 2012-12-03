#include "Addition.h"
#include "List.h"

namespace CAS {

double &Addition::accessMonomValue(MonomValues &values, Operands monom) const
{
    MonomValues::iterator it = std::find_if(begin(values), end(values),
            [&](const std::pair<std::vector<AbstractExpression*>, double> &item) {
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

AbstractExpression::ExpressionP Addition::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    Operands mergedOperands;
    mergedOperands.reserve(operands.size());
    for (const auto &operand : operands) {
        auto evalRes = operand->eval(scope, load, lazy, direct);
        if (typeid(*(evalRes)) == typeid(Addition)) {
            for (auto &childOp : static_cast<Addition*>(evalRes.get())->getOperands())
                mergedOperands.emplace_back(std::move(childOp));
        }
        else mergedOperands.emplace_back(std::move(evalRes));
    }
    MonomValues monomValues;
    double numberValue = 0;
    VectorExpression vec;
    std::map<unsigned int, Operands> listByDimension;
    std::map<std::vector<unsigned int>, Operands> matrixByDimensions;
    for (auto &operand : mergedOperands) {
        if (typeid(*operand) == typeid(NumberValue))
            numberValue += static_cast<NumberValue*>(operand.get())->getValue();
        else if (typeid(*operand) == typeid(LevelMultiplication)) {
            if (typeid(*(static_cast<LevelMultiplication*>(operand.get())->getOperands().front())) == typeid(NumberValue)) {
                double monomValue = std::move(static_cast<NumberValue*>(static_cast<LevelMultiplication*>(operand.get())->getOperands().front().get())->getValue());
                static_cast<LevelMultiplication*>(operand.get())->getOperands().erase(begin(static_cast<LevelMultiplication*>(operand.get())->getOperands()));
                accessMonomValue(monomValues, std::move(static_cast<LevelMultiplication*>(operand.get())->getOperands())) += monomValue;
            } else accessMonomValue(monomValues, std::move(static_cast<LevelMultiplication*>(operand.get())->getOperands()))++;
        } else if (typeid(*operand) == typeid(List)) {
                auto findRes = listByDimension.find(static_cast<List*>(operand.get())->getOperands().size());
                if (findRes == listByDimension.end())
                    listByDimension[static_cast<List*>(operand.get())->getOperands().size()] = std::move(static_cast<List*>(operand.get())->getOperands());
                else {
                    auto listIt = static_cast<List*>(operand.get())->getOperands().begin();
                    for (auto &cell : findRes->second)
                        cell = make_unique<Addition>(std::move(cell), std::move(*listIt++));
                }
        } else if (typeid(*operand) == typeid(VectorExpression)) {
            if (vec.getX() == nullptr) vec = std::move(*static_cast<VectorExpression*>(operand.get()));
            else vec = VectorExpression(Addition(std::move(static_cast<VectorExpression*>(operand.get())->getX()), std::move(vec.getX())).eval(scope, load, lazy, direct), Addition(std::move(static_cast<VectorExpression*>(operand.get())->getY()), std::move(vec.getY())).eval(scope, load, lazy, direct), Addition(std::move(static_cast<VectorExpression*>(operand.get())->getZ()), std::move(vec.getZ())).eval(scope, load, lazy, direct));
        /*} else if (typeid(*operand) == typeid(Matrix)) {
            auto findRes = matrixByDimensions.find(static_cast<Matrix*>(operand.get())->getOperands().size());
            if (findRes == matrixByDimensions.end())
                matrixByDimensions[static_cast<Matrix*>(operand.get())->getOperands().size()] = std::move(static_cast<Matrix*>(operand.get())->getOperands());
            else {
                auto listIt = static_cast<List*>(operand.get())->getOperands().begin();
                for (auto &cell : findRes->second)
                    cell = make_unique<Addition>(std::move(cell), std::move(*listIt++));
            }*/
        } else {
            Operands singleOpVec(1);
            singleOpVec.front() = std::move(operand);
            accessMonomValue(monomValues, std::move(singleOpVec))++;
        }
    }
    mergedOperands.clear();
    if (numberValue != 0) {
        if (vec.getX() != nullptr) {
            vec = VectorExpression(Addition(make_unique<NumberValue>(numberValue), std::move(vec.getX())).eval(scope, load, lazy, direct), Addition(make_unique<NumberValue>(numberValue), std::move(vec.getY())).eval(scope, load, lazy, direct), Addition(make_unique<NumberValue>(numberValue), std::move(vec.getZ())).eval(scope, load, lazy, direct));
        } else if (! listByDimension.empty()) {
            for (auto &cell : listByDimension.begin()->second)
                cell = make_unique<Addition>(std::move(cell), make_unique<NumberValue>(numberValue));
        } else mergedOperands.emplace_back(make_unique<NumberValue>(numberValue));
    }
    if (vec.getX() != nullptr) mergedOperands.emplace_back(make_unique<VectorExpression>(std::move(vec)));
    for (auto &list : listByDimension) mergedOperands.emplace_back(List(std::move(list.second)).eval(scope, load, lazy, direct));
    for (auto &item : monomValues) {
        Operands workaroundVec;
        for (const auto &monomItem : item.first) workaroundVec.emplace_back(monomItem);
        if (item.second != 0) {
            if (item.second != 1) {
                if (item.second < 0 && ! mergedOperands.empty()) {
                    ExpressionP subtr;
                    if (item.second != -1)
                        workaroundVec.emplace(begin(workaroundVec), make_unique<NumberValue>(-1 * item.second));
                    subtr = make_unique<Subtraction>(std::move(mergedOperands.back()), make_unique<LevelMultiplication>(std::move(workaroundVec)));
                    mergedOperands.erase(end(mergedOperands));
                    mergedOperands.emplace_back(std::move(subtr));
                } else {
                    workaroundVec.emplace(begin(workaroundVec), make_unique<NumberValue>(item.second));
                    mergedOperands.emplace_back(make_unique<LevelMultiplication>(std::move(workaroundVec)));
                }
            } else mergedOperands.emplace_back(make_unique<LevelMultiplication>(std::move(workaroundVec)));
        }
    }
    if (mergedOperands.size() == 0) return make_unique<NumberValue>(0);
    else if (mergedOperands.size() == 1) return std::move(mergedOperands.front());
    else return make_unique<Addition>(std::move(mergedOperands));
}

TypeInfo Addition::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    TypeCollection cp(candidates);
    cp.types.erase(TypeInfo::VOID);
    cp.types.erase(TypeInfo::BOOL);
    cp.listElementTypes.erase(TypeInfo::BOOL);
    cp.listElementTypes.erase(TypeInfo::VOID);
    auto num = cp.contains(TypeInfo::NUMBER);
    if (! num) cp.types.insert(TypeInfo::NUMBER);

    std::vector<const ExpressionP *> opRefs;
    opRefs.reserve(operands.size());
    for (const auto &op : operands) opRefs.emplace_back(&op);
    auto it = begin(opRefs), lastFail = end(opRefs);
    TypeInfo returnT = TypeInfo::NUMBER;
    while (! opRefs.empty()) {
        try {
            auto opT = (**it)->typeCheck(cp, scope);
            if (opT == TypeInfo::NUMBER) {
                if (opRefs.size() == 2 && ! num) cp.types.erase(opT);
            } else {
                cp = TypeCollection{{TypeInfo::NUMBER, opT}};
                returnT = std::move(opT);
            }
            it = opRefs.erase(it);
        } catch (const char *) {
            if (opRefs.size() == 1 || lastFail == it) throw "typing";
            else {
                ++it;
                lastFail = it;
            }
        }
        if (it == end(opRefs)) it = begin(opRefs);
    }
    return returnT;
}

/*
AbstractExpression::ExpressionP Addition::directEval() const
{
    double result;
    for (const auto &op : operands) {
        auto opRes = op->directEval().second;
        if (typeid(*opRes) != typeid(NumberValue)) throw "nodirectnonono";
        else result += static_cast<NumberValue*>(opRes)->getValue();
    }
    return make_unique<
}*/

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
