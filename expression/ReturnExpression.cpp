#include "ReturnExpression.h"

namespace CAS {

AbstractExpression::EvalRes ReturnExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    auto opRes = operand->eval(scope, load, lazy, direct);
    if (opRes.first == TypeInfo::VOID) throw "return type";
    return std::make_pair(opRes.first, make_unique<ReturnExpression>(std::move(opRes.second)));
}

bool ReturnExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(ReturnExpression) && operand->equals(static_cast<const ReturnExpression*>(other)->getOperand().get());
}

}
