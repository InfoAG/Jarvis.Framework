#include "Exponentiation.h"

namespace CAS {

AbstractExpression::ExpressionP Exponentiation::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    auto firstOpResult = first_op->eval(scope, load, lazy, direct), secondOpResult = second_op->eval(scope, load, lazy, direct);
    if (typeid(*(firstOpResult)) == typeid(NumberValue) && typeid(*(secondOpResult)) == typeid(NumberValue))
        return make_unique<NumberValue>(pow(*(static_cast<NumberValue*>(firstOpResult.get())), *(static_cast<NumberValue*>(secondOpResult.get()))));
    else if (typeid(*(firstOpResult)) == typeid(Exponentiation))
        return Exponentiation(std::move(static_cast<Exponentiation*>(firstOpResult.get())->getFirstOp()),
                              make_unique<LevelMultiplication>(std::move(static_cast<Exponentiation*>(firstOpResult.get())->getSecondOp()),
                                                          std::move(secondOpResult))).eval(scope, load, lazy, direct);
    else if (typeid(*(firstOpResult)) == typeid(NumberValue) && static_cast<NumberValue*>(firstOpResult.get())->getValue() == 1)
        return firstOpResult;
    else if (typeid(*(secondOpResult)) == typeid(NumberValue)) {
        if (static_cast<NumberValue*>(secondOpResult.get())->getValue() == 0)
            return make_unique<NumberValue>(1);
        else if (static_cast<NumberValue*>(secondOpResult.get())->getValue() == 1)
            return firstOpResult;
    }
    return make_unique<Exponentiation>(std::move(firstOpResult), std::move(secondOpResult));
}

TypeInfo Exponentiation::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    TypeCollection cp(candidates);
    cp.types.erase(TypeInfo::BOOL);
    cp.types.erase(TypeInfo::VOID);
    cp.listElementTypes.erase(TypeInfo::BOOL);
    cp.listElementTypes.erase(TypeInfo::VOID);
    second_op->typeCheck({{TypeInfo::NUMBER}}, scope);
    return first_op->typeCheck(cp, scope);
}


std::string Exponentiation::toString() const
{
    std::string result;
    if (typeid(*first_op) == typeid(Addition) || typeid(*first_op) == typeid(LevelMultiplication) || typeid(*first_op) == typeid(Division) || typeid(*first_op) == typeid(Subtraction) || typeid(*first_op) == typeid(Exponentiation))
        result = "(" + first_op->toString() + ")";
    else result = first_op->toString();
    result += "^";
    if (typeid(*second_op) == typeid(Addition) || typeid(*second_op) == typeid(LevelMultiplication) || typeid(*second_op) == typeid(Division) || typeid(*second_op) == typeid(Subtraction)) return result + "(" + second_op->toString() + ")";
    else return result + second_op->toString();
}


bool Exponentiation::equals(const AbstractExpression *other) const
{
    if (typeid(*other) != typeid(Exponentiation)) return false;
    const Exponentiation *casted = static_cast<const Exponentiation*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
