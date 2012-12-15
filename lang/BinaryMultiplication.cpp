#include "BinaryMultiplication.h"

namespace CAS {

AbstractExpression::ExpressionP BinaryMultiplication::executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    auto firstOpResult = first_op->executeExpression(scope, load, print, execOption), secondOpResult = second_op->executeExpression(scope, load, print, execOption);
    if (type == SCALARVECTOR) {
        if (typeid(*(firstOpResult)) == typeid(Vector) && typeid(*(secondOpResult)) == typeid(Vector)) {
            Expressions addOps;
            addOps.emplace_back(make_unique<LevelMultiplication>(std::move(static_cast<Vector*>(firstOpResult.get())->getX()), std::move(static_cast<Vector*>(secondOpResult.get())->getX())));
            addOps.emplace_back(make_unique<LevelMultiplication>(std::move(static_cast<Vector*>(firstOpResult.get())->getY()), std::move(static_cast<Vector*>(secondOpResult.get())->getY())));
            addOps.emplace_back(make_unique<LevelMultiplication>(std::move(static_cast<Vector*>(firstOpResult.get())->getZ()), std::move(static_cast<Vector*>(secondOpResult.get())->getZ())));
            return Addition(std::move(addOps)).executeExpression(scope, load, print, execOption);
        } else return make_unique<BinaryMultiplication>(std::move(firstOpResult), std::move(secondOpResult));
    } else return LevelMultiplication(std::move(firstOpResult), std::move(secondOpResult), (type == LEVELNUM)).executeExpression(scope, load, print, execOption);
}

TypeInfo BinaryMultiplication::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    TypeCollection cp(candidates);
    cp.types.erase(TypeInfo::VOID);
    cp.types.erase(TypeInfo::BOOL);
    cp.listElementTypes.erase(TypeInfo::BOOL);
    cp.listElementTypes.erase(TypeInfo::VOID);
    auto num = cp.contains(TypeInfo::NUMBER), vec = cp.contains(TypeInfo::VECTOR);
    cp.types.insert(TypeInfo::NUMBER);
    if (num) cp.types.insert(TypeInfo::VECTOR);
    try {
        auto firstOpT = first_op->typeCheck(cp, scope);
        if (firstOpT == TypeInfo::NUMBER) {
            if (! num) cp.types.erase(TypeInfo::NUMBER);
            if (! vec) cp.types.erase(TypeInfo::VECTOR);
            auto secondOpT = second_op->typeCheck(cp, scope);
            if (secondOpT == TypeInfo::NUMBER) type = LEVELNUM;
            else type = LEVEL;
            return secondOpT;
        } else if (firstOpT == TypeInfo::VECTOR) {
            if (! num) cp.types.erase(TypeInfo::VECTOR);
            else if (! vec) cp.types.erase(TypeInfo::NUMBER);
            auto secondOpT = second_op->typeCheck(cp, scope);
            if (secondOpT == TypeInfo::VECTOR) {
                type = SCALARVECTOR;
                return TypeInfo::NUMBER;
            } else {
                type = LEVEL;
                return TypeInfo::VECTOR;
            }
        } else {
            second_op->typeCheck({{TypeInfo::NUMBER, firstOpT}}, scope);
            return firstOpT;
        }
    } catch (UndecidableTypeException &) {
        auto secondOpT = second_op->typeCheck(cp, scope);
        if (secondOpT == TypeInfo::NUMBER) {
            if (! num) cp.types.erase(TypeInfo::NUMBER);
            if (! vec) cp.types.erase(TypeInfo::VECTOR);
            auto firstOpT = first_op->typeCheck(cp, scope);
            if (firstOpT == TypeInfo::NUMBER) type = LEVELNUM;
            else type = LEVEL;
            return firstOpT;
        } else if (secondOpT == TypeInfo::VECTOR) {
            if (! num) cp.types.erase(TypeInfo::VECTOR);
            else if (! vec) cp.types.erase(TypeInfo::NUMBER);
            auto firstOpT = first_op->typeCheck(cp, scope);
            if (firstOpT == TypeInfo::VECTOR) {
                type = SCALARVECTOR;
                return TypeInfo::NUMBER;
            } else {
                type = LEVEL;
                return TypeInfo::VECTOR;
            }
        } else {
            first_op->typeCheck({{TypeInfo::NUMBER, secondOpT}}, scope);
            return secondOpT;
        }
}
}

AbstractExpression::ExpressionP BinaryMultiplication::differentiate(const std::string &var) const
{
    return make_unique<Addition>(make_unique<LevelMultiplication>(first_op->differentiate(var), second_op->copyEx()), make_unique<LevelMultiplication>(first_op->copyEx(), second_op->differentiate(var)));
}

bool BinaryMultiplication::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(BinaryMultiplication) && first_op->equals(static_cast<const BinaryMultiplication*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const BinaryMultiplication*>(other)->getSecondOp().get());
}

}
