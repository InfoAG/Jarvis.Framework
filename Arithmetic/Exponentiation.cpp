#include "Exponentiation.h"

namespace CAS {

std::unique_ptr<CAS::AbstractArithmetic> Exponentiation::eval(const EvalInfo &ei) const
{
    auto firstOpResult = first_op->eval(ei), secondOpResult = second_op->eval(ei);
    if (firstOpResult->getType() == NUMBERARITH && secondOpResult->getType() == NUMBERARITH)
        return make_unique<NumberArith>(pow(*(static_cast<NumberArith*>(firstOpResult.get())), *(static_cast<NumberArith*>(secondOpResult.get()))));
    else if (firstOpResult->getType() == NUMBERARITH && static_cast<NumberArith*>(firstOpResult.get())->getValue() == 1)
        return firstOpResult;
    else if (secondOpResult->getType() == NUMBERARITH && static_cast<NumberArith*>(secondOpResult.get())->getValue() == 0)
        return make_unique<NumberArith>(1);
    else return make_unique<Exponentiation>(std::move(firstOpResult), std::move(secondOpResult));
}
bool Exponentiation::isEqual(const AbstractArithmetic *other) const
{
    if (other->getType() != EXPONENTIATION) return false;
    const Exponentiation *casted = static_cast<const Exponentiation*>(other);
    return first_op->isEqual(casted->getFirstOp()) && second_op->isEqual(casted->getSecondOp());
}

}
