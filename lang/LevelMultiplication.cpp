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

AbstractExpression::ExpressionP LevelMultiplication::executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    Expressions mergedExpressions;
    for (const auto &operand : operands) {
        auto evalRes = operand->executeExpression(scope, load, print, execOption);
        if (typeid(*(evalRes)) == typeid(LevelMultiplication)) {
            for (auto &childOp : static_cast<LevelMultiplication*>(evalRes.get())->getOperands())
                mergedExpressions.emplace_back(std::move(childOp));
        }
        else mergedExpressions.emplace_back(std::move(evalRes));
    }
    double numberValue = 1;
    BasisValues basisValues;
    Vector vec;
    std::map<unsigned int, Expressions> listByDimension;

    // http://www.iaeng.org/publication/WCE2010/WCE2010_pp1829-1833.pdf


    while (! mergedExpressions.empty()) {
        auto &operand = mergedExpressions.front();
        if (typeid(*operand) == typeid(NumberValue))
            numberValue *= static_cast<NumberValue*>(operand.get())->getValue();
        else if (typeid(*operand) == typeid(Vector))
            vec = std::move(*static_cast<Vector*>(operand.get()));
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
            addToBasisValue(basisValues, std::move(operand), make_unique<NumberValue>(1));
        mergedExpressions.erase(begin(mergedExpressions));
    }
    mergedExpressions.clear();
    if (returnsNumber && numberValue == 0) return make_unique<NumberValue>(0);
    else {
        if (numberValue == 1) {
            if (vec.getX() != nullptr)
                mergedExpressions.emplace_back(make_unique<Vector>(std::move(vec)));
        } else {
            if (vec.getX() != nullptr) {
                vec = *static_cast<Vector*>(Vector(make_unique<LevelMultiplication>(make_unique<NumberValue>(numberValue), std::move(vec.getX())), make_unique<LevelMultiplication>(make_unique<NumberValue>(numberValue), std::move(vec.getY())), make_unique<LevelMultiplication>(make_unique<NumberValue>(numberValue), std::move(vec.getZ()))).executeExpression(scope, load, print, execOption).get());
                mergedExpressions.emplace_back(make_unique<Vector>(std::move(vec)));
            } else if (! listByDimension.empty()) {
                for (auto &cell : listByDimension.begin()->second)
                    cell = make_unique<BinaryMultiplication>(std::move(cell), make_unique<NumberValue>(numberValue));
            } else mergedExpressions.emplace_back(make_unique<NumberValue>(numberValue));
        }
        for (auto &basisValue : basisValues)
            mergedExpressions.emplace_back(Exponentiation(std::move(basisValue.first), std::move(basisValue.second)).executeExpression(scope, load, print, execOption));
        for (auto &list : listByDimension)
            mergedExpressions.emplace_back(List(std::move(list.second)).executeExpression(scope, load, print, execOption));
        if (mergedExpressions.size() == 1) return std::move(mergedExpressions.front());
        else if (mergedExpressions.empty()) return make_unique<NumberValue>(1);
        else return make_unique<LevelMultiplication>(std::move(mergedExpressions));
    }
}

TypeInfo LevelMultiplication::typeCheck(const TypeCollection &candidates, Scope &scope)
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
        } catch (UndecidableTypeException &e) {
            if (opRefs.size() == 1 || lastFail == it) throw e;
            else {
                ++it;
                lastFail = it;
            }
        }
        if (it == end(opRefs)) it = begin(opRefs);
    }
    if (returnT == TypeInfo::NUMBER) returnsNumber = true;
    return returnT;
}

AbstractExpression::ExpressionP LevelMultiplication::differentiate(const std::string &var) const
{
    auto result = operands.front()->copyEx();
    for (auto it = operands.cbegin() + 1; it != operands.cend(); ++it)
        result = make_unique<Addition>(make_unique<LevelMultiplication>(result->differentiate(var), (*it)->copyEx()), make_unique<LevelMultiplication>(result->copyEx(), (*it)->differentiate(var)));
    return result;
}

std::string LevelMultiplication::toString() const
{
    std::string result;
    for (auto it = operands.cbegin(); it != operands.cend(); ++it) {
        if (typeid(**it) == typeid(Subtraction) || typeid(**it) == typeid(Addition)) result += "(" + (*it)->toString() + ")";
        else result += (*it)->toString();
        if (it != operands.cend() - 1) result += "*";
    }
    return result;
}

bool LevelMultiplication::equals(const AbstractStatement *other) const
{
    if (typeid(*other) != typeid(LevelMultiplication)) return false;
    return equalOperands(static_cast<const LevelMultiplication*>(other)->getOperands(), operands);
}

}
