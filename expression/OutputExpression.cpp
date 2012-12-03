#include "OutputExpression.h"

namespace CAS {

TypeInfo OutputExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (candidates.contains(TypeInfo::VOID)) {
        operand->typeCheck(TypeCollection::all(), scope);
        return TypeInfo::VOID;
    } else throw "typing";
}

bool OutputExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(OutputExpression) && operand->equals(static_cast<const OutputExpression*>(other)->getOperand().get());
}

}
