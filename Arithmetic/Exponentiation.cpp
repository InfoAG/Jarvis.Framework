#include "Exponentiation.h"

namespace CAS {

AbstractExpression::EvalRes Exponentiation::eval(Scope &scope, bool lazy) const
{
    auto firstOpResult = first_op->eval(scope, lazy), secondOpResult = second_op->eval(scope, lazy);
    if (typeid(*(firstOpResult.second)) == typeid(NumberArith) && typeid(*(secondOpResult.second)) == typeid(NumberArith))
        return std::make_pair(NUMBER, make_unique<NumberArith>(pow(*(static_cast<NumberArith*>(firstOpResult.second.get())), *(static_cast<NumberArith*>(secondOpResult.second.get())))));
    else if (typeid(*(firstOpResult.second)) == typeid(Exponentiation))
        return Exponentiation(std::move(static_cast<Exponentiation*>(firstOpResult.second.get())->getFirstOp()),
                              make_unique<LevelMultiplication>(std::move(static_cast<Exponentiation*>(firstOpResult.second.get())->getSecondOp()),
                                                          std::move(secondOpResult.second))).eval(scope, lazy);
    else if (typeid(*(firstOpResult.second)) == typeid(NumberArith) && static_cast<NumberArith*>(firstOpResult.second.get())->getValue() == 1)
        return firstOpResult;
    else if (typeid(*(secondOpResult.second)) == typeid(NumberArith)) {
        if (static_cast<NumberArith*>(secondOpResult.second.get())->getValue() == 0)
            return std::make_pair(NUMBER, make_unique<NumberArith>(1));
        else if (static_cast<NumberArith*>(secondOpResult.second.get())->getValue() == 1)
            return firstOpResult;
    }
    return std::make_pair(NUMBER, make_unique<Exponentiation>(std::move(firstOpResult.second), std::move(secondOpResult.second)));
}


std::string Exponentiation::toString() const
{
    std::string result;
    if (typeid(*first_op) == typeid(Addition) || typeid(*first_op) == typeid(LevelMultiplication) || typeid(*first_op) == typeid(Division) || typeid(*first_op) == typeid(Subtraction) || typeid(*first_op) == typeid(Exponentiation))
        result = "(" + first_op->toString() + ")";
    else result = first_op->toString();
    result += "^";
    if (typeid(*second_op) == typeid(Addition) || typeid(*second_op) == typeid(LevelMultiplication) || typeid(*second_op) == typeid(Division) || typeid(*second_op) == typeid(Subtraction)) return result + "(" + second_op->toString() + ")";
    else return result + second_op->toString();
}


bool Exponentiation::equals(const AbstractExpression *other) const
{
    if (typeid(*other) != typeid(Exponentiation)) return false;
    const Exponentiation *casted = static_cast<const Exponentiation*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
