#include "LogicalOrExpression.h"

namespace CAS {

AbstractExpression::ExpressionP LogicalOrExpression::execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const
{
    auto firstOpResult = first_op->execute(scope, load, execOption), secondOpResult = second_op->execute(scope, load, execOption);
    if (typeid(*(firstOpResult)) == typeid(BoolValue) && typeid(*(secondOpResult)) == typeid(BoolValue))
        return make_unique<BoolValue>(static_cast<BoolValue*>(firstOpResult.get())->value() || static_cast<BoolValue*>(secondOpResult.get())->value());
    else return make_unique<LogicalOrExpression>(std::move(firstOpResult), std::move(secondOpResult));
}

TypeInfo LogicalOrExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::BOOL);
    first_op->typeCheck({{TypeInfo::BOOL}}, scope);
    second_op->typeCheck({{TypeInfo::BOOL}}, scope);
    return TypeInfo::BOOL;
}

bool LogicalOrExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(LogicalOrExpression) && first_op->equals(static_cast<const LogicalOrExpression*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const LogicalOrExpression*>(other)->getFirstOp().get());
}

}
