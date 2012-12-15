#include "NaturalLogarithm.h"

namespace CAS {

AbstractExpression::ExpressionP NaturalLogarithm::executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    auto opRes = operand->executeExpression(scope, load, print, execOption);
    if (typeid(*opRes) == typeid(NumberValue))
        return make_unique<NumberValue>(log(static_cast<NumberValue*>(opRes.get())->getValue()));
    else return make_unique<NaturalLogarithm>(std::move(opRes));
}

TypeInfo NaturalLogarithm::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::NUMBER);
    operand->typeCheck({{TypeInfo::NUMBER}}, scope);
    return TypeInfo::NUMBER;
}

AbstractExpression::ExpressionP NaturalLogarithm::differentiate(const std::string &var) const
{
    return make_unique<LevelMultiplication>(operand->differentiate(var), make_unique<Division>(make_unique<NumberValue>(1), operand->copyEx()));
}

bool NaturalLogarithm::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(NaturalLogarithm) && *this == *static_cast<const NaturalLogarithm*>(other);
}

}
