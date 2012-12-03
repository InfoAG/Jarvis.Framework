#include "LazyEval.h"

namespace CAS {

TypeInfo LazyEval::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    TypeCollection cp(candidates);
    cp.types.erase(TypeInfo::VOID);
    return operand->typeCheck(cp, scope);
}

bool LazyEval::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(LazyEval) && static_cast<const LazyEval*>(other)->getOperand()->equals(operand.get());
}

}
