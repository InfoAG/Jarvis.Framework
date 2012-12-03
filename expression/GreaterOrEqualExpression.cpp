#include "GreaterOrEqualExpression.h"

namespace CAS {

AbstractExpression::ExpressionP GreaterOrEqualExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    auto firstOpResult = first_op->eval(scope, load, lazy, direct), secondOpResult = second_op->eval(scope, load, lazy, direct);
    if (typeid(*(firstOpResult)) == typeid(NumberValue) && typeid(*(secondOpResult)) == typeid(NumberValue))
        return make_unique<BoolValue>(static_cast<NumberValue*>(firstOpResult.get())->getValue() < static_cast<NumberValue*>(secondOpResult.get())->getValue());
    else return make_unique<GreaterOrEqualExpression>(std::move(firstOpResult), std::move(secondOpResult));
}

TypeInfo GreaterOrEqualExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
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

bool GreaterOrEqualExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(GreaterOrEqualExpression) && first_op->equals(static_cast<const GreaterOrEqualExpression*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const GreaterOrEqualExpression*>(other)->getFirstOp().get());
}

}
