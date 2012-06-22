#include "Addition.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Addition::eval(const EvalInfo &ei) const
{
    if (first_op->getType() == NUMBERARITH && second_op->getType() == NUMBERARITH)
        return std::unique_ptr<NumberArith>(new NumberArith(*(static_cast<NumberArith*>(first_op.get())) + *(static_cast<NumberArith*>(second_op.get()))));
    else return this->copy();
}

}
