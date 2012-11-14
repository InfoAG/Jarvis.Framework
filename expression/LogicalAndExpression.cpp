#include "LogicalAndExpression.h"

namespace CAS {

AbstractExpression::EvalRes LogicalAndExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    auto firstOpResult = first_op->eval(scope, load, lazy, direct), secondOpResult = second_op->eval(scope, load, lazy, direct);
    if (firstOpResult.first != TypeInfo::BOOL || secondOpResult.first != TypeInfo::BOOL) throw "args derp";
    else if (typeid(*(firstOpResult.second)) == typeid(BoolValue) && typeid(*(secondOpResult.second)) == typeid(BoolValue))
        return std::make_pair(TypeInfo::BOOL, make_unique<BoolValue>(static_cast<BoolValue*>(firstOpResult.second.get())->value() && static_cast<BoolValue*>(secondOpResult.second.get())->value()));
    else return std::make_pair(TypeInfo::BOOL, make_unique<LogicalAndExpression>(std::move(firstOpResult.second), std::move(secondOpResult.second)));
}

bool LogicalAndExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(LogicalAndExpression) && first_op->equals(static_cast<const LogicalAndExpression*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const LogicalAndExpression*>(other)->getFirstOp().get());
}

}
