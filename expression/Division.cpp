#include "Division.h"
#include "List.h"
#include "VectorExpression.h"

namespace CAS {

AbstractExpression::ExpressionP Division::execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const
{
    /*auto firstOpResult = first_op->execute(scope, load, execOption), secondOpResult = second_op->execute(scope, load, execOption);
    if (typeid(*(firstOpResult)) == typeid(NumberValue)) {
        if (typeid(*(secondOpResult)) == typeid(NumberValue))
            return make_unique<NumberValue>(*static_cast<NumberValue*>(firstOpResult.get()) / *static_cast<NumberValue*>(secondOpResult.get()));
        else if (typeid(*(firstOpResult)) == typeid(NumberValue) && typeid(*(secondOpResult)) == typeid(List))
            return List(*static_cast<NumberValue*>(firstOpResult.get()) / *static_cast<List*>(secondOpResult.get())).execute(scope, load, execOption);
        else if (typeid(*(firstOpResult)) == typeid(NumberValue) && typeid(*(secondOpResult)) == typeid(VectorExpression))
            return VectorExpression(*static_cast<NumberValue*>(firstOpResult.get()) / *static_cast<VectorExpression*>(secondOpResult.get())).execute(scope, load, execOption);
    } else if (typeid(*(firstOpResult)) == typeid(List)) {
        if (typeid(*(secondOpResult)) == typeid(NumberValue))
            return List(*static_cast<List*>(firstOpResult.get()) / *static_cast<NumberValue*>(secondOpResult.get())).execute(scope, load, execOption);
        else if (typeid(*(secondOpResult)) == typeid(List))
            return List(*static_cast<List*>(firstOpResult.get()) / *static_cast<List*>(secondOpResult.get())).execute(scope, load, execOption);
    } else if (typeid(*(firstOpResult)) == typeid(VectorExpression)) {
        if (typeid(*(secondOpResult)) == typeid(NumberValue))
            return VectorExpression(*static_cast<VectorExpression*>(firstOpResult.get()) / *static_cast<NumberValue*>(secondOpResult.get())).execute(scope, load, execOption);
        else if (typeid(*(secondOpResult)) == typeid(VectorExpression))
            return VectorExpression(*static_cast<VectorExpression*>(firstOpResult.get()) / *static_cast<VectorExpression*>(secondOpResult.get())).execute(scope, load, execOption);
    }
    if (typeid(*(secondOpResult)) == typeid(NumberValue) && static_cast<NumberValue*>(secondOpResult.get())->getValue() == 1)
        return firstOpResult;
    else return make_unique<Division>(std::move(firstOpResult), std::move(secondOpResult));*/
    return BinaryMultiplication(first_op->copy(), make_unique<Exponentiation>(second_op->copy(), make_unique<NumberValue>(-1))).execute(scope, load, execOption);
}

TypeInfo Division::typeCheck(const TypeCollection &candidates, Scope &scope)
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

AbstractExpression::ExpressionP Division::differentiate(const std::string &var) const
{
    return make_unique<Division>(make_unique<Subtraction>(make_unique<LevelMultiplication>(first_op->differentiate(var), second_op->copy()), make_unique<LevelMultiplication>(first_op->copy(), second_op->differentiate(var))), make_unique<Exponentiation>(second_op->copy(), make_unique<NumberValue>(2)));
}


std::string Division::toString() const
{
    std::string result;
    if (typeid(*first_op) == typeid(Addition) || typeid(*first_op) == typeid(Subtraction))
        result = "(" + first_op->toString() + ")";
    else result = first_op->toString();
    result += "/";
    if (typeid(*second_op) == typeid(Addition) || typeid(*second_op) == typeid(LevelMultiplication) || typeid(*second_op) == typeid(Division) || typeid(*second_op) == typeid(Subtraction)) return result + "(" + second_op->toString() + ")";
    else return result + second_op->toString();
}

bool Division::equals(const AbstractExpression *other) const
{
    if (typeid(*other) != typeid(Division)) return false;
    const Division *casted = static_cast<const Division*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
