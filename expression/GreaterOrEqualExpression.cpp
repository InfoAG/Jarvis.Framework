#include "GreaterOrEqualExpression.h"

namespace CAS {

AbstractExpression::EvalRes GreaterOrEqualExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    auto firstOpResult = first_op->eval(scope, load, lazy, direct), secondOpResult = second_op->eval(scope, load, lazy, direct);
    if (firstOpResult.first != TypeInfo::NUMBER || secondOpResult.first != TypeInfo::NUMBER) throw "(:";
    else if (typeid(*(firstOpResult.second)) == typeid(NumberArith) && typeid(*(secondOpResult.second)) == typeid(NumberArith))
        return std::make_pair(TypeInfo::BOOL, make_unique<BoolValue>(static_cast<NumberArith*>(firstOpResult.second.get())->getValue() < static_cast<NumberArith*>(secondOpResult.second.get())->getValue()));
    else return std::make_pair(TypeInfo::BOOL, make_unique<GreaterOrEqualExpression>(std::move(firstOpResult.second), std::move(secondOpResult.second)));
}

bool GreaterOrEqualExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(GreaterOrEqualExpression) && first_op->equals(static_cast<const GreaterOrEqualExpression*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const GreaterOrEqualExpression*>(other)->getFirstOp().get());
}

}
