#include "LessOrEqualExpression.h"

namespace CAS {

AbstractExpression::ExpressionP LessOrEqualExpression::execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const
{
    auto firstOpResult = first_op->execute(scope, load, execOption), secondOpResult = second_op->execute(scope, load, execOption);
    if (typeid(*(firstOpResult)) == typeid(NumberValue) && typeid(*(secondOpResult)) == typeid(NumberValue))
        return make_unique<BoolValue>(static_cast<NumberValue*>(firstOpResult.get())->getValue() < static_cast<NumberValue*>(secondOpResult.get())->getValue());
    else return make_unique<LessOrEqualExpression>(std::move(firstOpResult), std::move(secondOpResult));
}

TypeInfo LessOrEqualExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
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

bool LessOrEqualExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(LessOrEqualExpression) && first_op->equals(static_cast<const LessOrEqualExpression*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const LessOrEqualExpression*>(other)->getFirstOp().get());
}

}
