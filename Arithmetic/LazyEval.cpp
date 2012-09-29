#include "LazyEval.h"

namespace CAS {

bool LazyEval::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(LazyEval) && static_cast<const LazyEval*>(other)->getOperand()->equals(operand.get());
}

}
