#include "Exponentiation.h"

namespace CAS {

std::unique_ptr<CAS::AbstractExpression> Exponentiation::eval(Scope &scope, bool lazy) const
{
    auto firstOpResult = first_op->eval(scope, lazy), secondOpResult = second_op->eval(scope, lazy);
    if (typeid(*firstOpResult) == typeid(NumberArith) && typeid(*secondOpResult) == typeid(NumberArith))
        return make_unique<NumberArith>(pow(*(static_cast<NumberArith*>(firstOpResult.get())), *(static_cast<NumberArith*>(secondOpResult.get()))));
    else if (typeid(*firstOpResult) == typeid(Exponentiation))
        return Exponentiation(std::move(static_cast<Exponentiation*>(firstOpResult.get())->getFirstOp()),
                              make_unique<Multiplication>(std::move(static_cast<Exponentiation*>(firstOpResult.get())->getSecondOp()),
                                                          std::move(secondOpResult))).eval(scope, lazy);
    else if (typeid(*firstOpResult) == typeid(NumberArith) && static_cast<NumberArith*>(firstOpResult.get())->getValue() == 1)
        return firstOpResult;
    else if (typeid(*secondOpResult) == typeid(NumberArith)) {
        if (static_cast<NumberArith*>(secondOpResult.get())->getValue() == 0)
            return make_unique<NumberArith>(1);
        else if (static_cast<NumberArith*>(secondOpResult.get())->getValue() == 1)
            return firstOpResult;
    }
    return make_unique<Exponentiation>(std::move(firstOpResult), std::move(secondOpResult));
}


std::string Exponentiation::toString() const
{
    std::string result;
    if (typeid(*first_op) == typeid(Addition) || typeid(*first_op) == typeid(Multiplication) || typeid(*first_op) == typeid(Division) || typeid(*first_op) == typeid(Subtraction) || typeid(*first_op) == typeid(Exponentiation))
        result = "(" + first_op->toString() + ")";
    else result = first_op->toString();
    result += "^";
    if (typeid(*second_op) == typeid(Addition) || typeid(*second_op) == typeid(Multiplication) || typeid(*second_op) == typeid(Division) || typeid(*second_op) == typeid(Subtraction)) return result + "(" + second_op->toString() + ")";
    else return result + second_op->toString();
}


bool Exponentiation::equals(const AbstractExpression *other) const
{
    if (typeid(*other) != typeid(Exponentiation)) return false;
    const Exponentiation *casted = static_cast<const Exponentiation*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
