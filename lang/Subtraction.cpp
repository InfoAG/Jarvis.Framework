#include "Subtraction.h"

namespace CAS {

AbstractExpression::ExpressionP Subtraction::executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    auto first_op_result = first_op->executeExpression(scope, load, print, execOption), second_op_result = second_op->executeExpression(scope, load, print, execOption);
    if (typeid(first_op_result) == typeid(NumberValue) && typeid(second_op_result) == typeid(NumberValue))
        return make_unique<NumberValue>(*(static_cast<NumberValue*>(first_op_result.get())) - *(static_cast<NumberValue*>(second_op_result.get())));
    else return Addition(std::move(first_op_result), make_unique<LevelMultiplication>(make_unique<NumberValue>(-1), std::move(second_op_result))).executeExpression(scope, load, print, execOption);
}

TypeInfo Subtraction::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    TypeCollection cp(candidates);
    cp.types.erase(TypeInfo::VOID);
    cp.types.erase(TypeInfo::BOOL);
    cp.listElementTypes.erase(TypeInfo::BOOL);
    cp.listElementTypes.erase(TypeInfo::VOID);
    auto num = cp.contains(TypeInfo::NUMBER);
    if (! num) cp.types.insert(TypeInfo::NUMBER);
    try {
        auto firstOpT = first_op->typeCheck(cp, scope);
        if (firstOpT == TypeInfo::NUMBER) {
            if (! num) cp.types.erase(TypeInfo::NUMBER);
            return second_op->typeCheck(cp, scope);
        } else {
            second_op->typeCheck({{TypeInfo::NUMBER, firstOpT}}, scope);
            return firstOpT;
        }
    } catch (UndecidableTypeException &) {
        auto secondOpT = second_op->typeCheck(cp, scope);
        if (secondOpT == TypeInfo::NUMBER) {
            if (! num) cp.types.erase(TypeInfo::NUMBER);
            return second_op->typeCheck(cp, scope);
        } else {
            first_op->typeCheck({{TypeInfo::NUMBER, secondOpT}}, scope);
            return secondOpT;
        }
    }
}

std::string Subtraction::toString() const
{
    std::string result;
    if (typeid(*first_op) == typeid(Addition))
        result = "(" + first_op->toString() + ")";
    else result = first_op->toString();
    result += "-";
    if (typeid(*second_op) == typeid(Addition) || typeid(*second_op) == typeid(Subtraction)) return result + "(" + second_op->toString() + ")";
    else return result + second_op->toString();
}

bool Subtraction::equals(const AbstractStatement *other) const
{
    if (typeid(*other) != typeid(Subtraction)) return false;
    const Subtraction *casted = static_cast<const Subtraction*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
