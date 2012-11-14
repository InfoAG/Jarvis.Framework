#include "NegationExpression.h"

namespace CAS {

AbstractExpression::EvalRes NegationExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    auto operandRes = operand->eval(scope, load, lazy, direct);
    if (operandRes.first != TypeInfo::BOOL) throw "type derp";
    else if (typeid(*(operandRes.second)) == typeid(BoolValue))
        return std::make_pair(TypeInfo::BOOL, make_unique<BoolValue>(! static_cast<BoolValue*>(operandRes.second.get())->value()));
    else return std::make_pair(TypeInfo::BOOL, make_unique<NegationExpression>(std::move(operandRes.second)));
}

bool NegationExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(NegationExpression) && operand->equals(static_cast<const NegationExpression*>(other)->getOperand().get());
}

}
