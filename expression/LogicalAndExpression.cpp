#include "LogicalAndExpression.h"

namespace CAS {

AbstractExpression::ExpressionP LogicalAndExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    auto firstOpResult = first_op->eval(scope, load, lazy, direct), secondOpResult = second_op->eval(scope, load, lazy, direct);
    if (typeid(*(firstOpResult)) == typeid(BoolValue) && typeid(*(secondOpResult)) == typeid(BoolValue))
        return make_unique<BoolValue>(static_cast<BoolValue*>(firstOpResult.get())->value() && static_cast<BoolValue*>(secondOpResult.get())->value());
    else return make_unique<LogicalAndExpression>(std::move(firstOpResult), std::move(secondOpResult));
}

TypeInfo LogicalAndExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (candidates.contains(TypeInfo::BOOL)) {
        first_op->typeCheck({{TypeInfo::BOOL}}, scope);
        second_op->typeCheck({{TypeInfo::BOOL}}, scope);
        return TypeInfo::BOOL;
    } else throw "typing";
}

bool LogicalAndExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(LogicalAndExpression) && first_op->equals(static_cast<const LogicalAndExpression*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const LogicalAndExpression*>(other)->getFirstOp().get());
}

}
