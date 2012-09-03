#include "Exponentiation.h"

namespace CAS {

std::unique_ptr<CAS::AbstractArithmetic> Exponentiation::eval(const EvalInfo &ei) const
{
    auto firstOpResult = first_op->eval(ei), secondOpResult = second_op->eval(ei);
    if (firstOpResult->type() == NUMBERARITH && secondOpResult->type() == NUMBERARITH)
        return make_unique<NumberArith>(pow(*(static_cast<NumberArith*>(firstOpResult.get())), *(static_cast<NumberArith*>(secondOpResult.get()))));
    else if (firstOpResult->type() == EXPONENTIATION)
        return make_unique<Exponentiation>(std::move(static_cast<Exponentiation*>(firstOpResult.get())->getFirstOp()), make_unique<Multiplication>(std::move(static_cast<Exponentiation*>(firstOpResult.get())->getSecondOp()), std::move(secondOpResult)));
    else if (firstOpResult->type() == NUMBERARITH && static_cast<NumberArith*>(firstOpResult.get())->getValue() == 1)
        return firstOpResult;
    else if (secondOpResult->type() == NUMBERARITH) {
        if (static_cast<NumberArith*>(secondOpResult.get())->getValue() == 0)
            return make_unique<NumberArith>(1);
        else if (static_cast<NumberArith*>(secondOpResult.get())->getValue() == 1)
            return firstOpResult;
    }
    return make_unique<Exponentiation>(std::move(firstOpResult), std::move(secondOpResult));
}
bool Exponentiation::equals(const AbstractArithmetic *other) const
{
    if (other->type() != EXPONENTIATION) return false;
    const Exponentiation *casted = static_cast<const Exponentiation*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
