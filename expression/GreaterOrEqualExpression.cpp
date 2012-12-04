#include "GreaterOrEqualExpression.h"

namespace CAS {

AbstractExpression::ExpressionP GreaterOrEqualExpression::execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const
{
    auto firstOpResult = first_op->execute(scope, load, execOption), secondOpResult = second_op->execute(scope, load, execOption);
    if (typeid(*(firstOpResult)) == typeid(NumberValue) && typeid(*(secondOpResult)) == typeid(NumberValue))
        return make_unique<BoolValue>(static_cast<NumberValue*>(firstOpResult.get())->getValue() < static_cast<NumberValue*>(secondOpResult.get())->getValue());
    else return make_unique<GreaterOrEqualExpression>(std::move(firstOpResult), std::move(secondOpResult));
}

TypeInfo GreaterOrEqualExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::BOOL);
    TypeCollection opCol{TypeCollection::all()};
    opCol.erase(TypeInfo::VOID);
    try {
        second_op->typeCheck({{first_op->typeCheck(opCol, scope)}}, scope);
        return TypeInfo::BOOL;
    } catch (UndecidableTypeException &) {
        first_op->typeCheck({{second_op->typeCheck(opCol, scope)}}, scope);
        return TypeInfo::BOOL;
    }
}

bool GreaterOrEqualExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(GreaterOrEqualExpression) && first_op->equals(static_cast<const GreaterOrEqualExpression*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const GreaterOrEqualExpression*>(other)->getFirstOp().get());
}

}
