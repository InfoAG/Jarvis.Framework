#include "Addition.h"

namespace CAS {

AbstractArithmetic *Addition::eval(const EvalInfo &ei) const
{
    if (first_op->getType() == NUMBER && second_op->getType() == NUMBER)
        return new Number(*(static_cast<Number*>(first_op)) + *(static_cast<Number*>(second_op)));
    else return this->copy();
}

}
