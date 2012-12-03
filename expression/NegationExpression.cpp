#include "NegationExpression.h"

namespace CAS {

AbstractExpression::ExpressionP NegationExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    auto operandRes = operand->eval(scope, load, lazy, direct);
    if (typeid(*(operandRes)) == typeid(BoolValue))
        return make_unique<BoolValue>(! static_cast<BoolValue*>(operandRes.get())->value());
    else return make_unique<NegationExpression>(std::move(operandRes));
}

TypeInfo NegationExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (candidates.contains(TypeInfo::BOOL)) {
        operand->typeCheck({{TypeInfo::BOOL}}, scope);
        return TypeInfo::BOOL;
    } else throw "typing";
}

bool NegationExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(NegationExpression) && operand->equals(static_cast<const NegationExpression*>(other)->getOperand().get());
}

}
