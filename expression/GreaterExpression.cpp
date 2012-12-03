#include "GreaterExpression.h"

namespace CAS {

AbstractExpression::ExpressionP GreaterExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    auto firstOpResult = first_op->eval(scope, load, lazy, direct), secondOpResult = second_op->eval(scope, load, lazy, direct);
    if (typeid(*(firstOpResult)) == typeid(NumberValue) && typeid(*(secondOpResult)) == typeid(NumberValue))
        return make_unique<BoolValue>(static_cast<NumberValue*>(firstOpResult.get())->getValue() < static_cast<NumberValue*>(secondOpResult.get())->getValue());
    else return make_unique<GreaterExpression>(std::move(firstOpResult), std::move(secondOpResult));
}

TypeInfo GreaterExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (! candidates.contains(TypeInfo::BOOL)) throw "typing";
    TypeCollection opCol{TypeCollection::all()};
    opCol.erase(TypeInfo::VOID);
    try {
        second_op->typeCheck({{first_op->typeCheck(opCol, scope)}}, scope);
        return TypeInfo::BOOL;
    } catch (const char *) {
        first_op->typeCheck({{second_op->typeCheck(opCol, scope)}}, scope);
        return TypeInfo::BOOL;
    }
}

bool GreaterExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(GreaterExpression) && first_op->equals(static_cast<const GreaterExpression*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const GreaterExpression*>(other)->getFirstOp().get());
}

}
