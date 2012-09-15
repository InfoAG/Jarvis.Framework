#include "LazyEval.h"

namespace CAS {

bool LazyEval::equals(const AbstractArithmetic *other) const
{
    return other->type() == LAZYEVAL && static_cast<const LazyEval*>(other)->getOperand()->equals(operand.get());
}

}
