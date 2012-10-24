#include "BinaryMultiplication.h"

namespace CAS {

AbstractExpression::EvalRes BinaryMultiplication::eval(Scope &scope, bool lazy) const
{
    auto firstOpResult = first_op->eval(scope, lazy), secondOpResult = second_op->eval(scope, lazy);
    if (firstOpResult.first == NUMBER && secondOpResult.first == NUMBER)
        return LevelMultiplication(std::move(firstOpResult.second), std::move(secondOpResult.second)).eval(scope, lazy);
    else return std::make_pair(LIST, copy());
}

bool BinaryMultiplication::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(BinaryMultiplication) && first_op->equals(static_cast<const BinaryMultiplication*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const BinaryMultiplication*>(other)->getSecondOp().get());
}

}
