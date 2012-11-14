#include "Division.h"

namespace CAS {

AbstractExpression::EvalRes Division::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    auto firstOpResult = first_op->eval(scope, load, lazy, direct), secondOpResult = second_op->eval(scope, load, lazy, direct);
    if (firstOpResult.second->equals(secondOpResult.second.get()))
        return std::make_pair(TypeInfo{TypeInfo::NUMBER}, make_unique<NumberArith>(1));
    else if (typeid(*(firstOpResult.second)) == typeid(NumberArith) && typeid(*(secondOpResult.second)) == typeid(NumberArith))
        return std::make_pair(TypeInfo{TypeInfo::NUMBER}, make_unique<NumberArith>(*(static_cast<NumberArith*>(firstOpResult.second.get())) / *(static_cast<NumberArith*>(secondOpResult.second.get()))));
    else if ((typeid(*(firstOpResult.second)) == typeid(NumberArith) && static_cast<NumberArith*>(firstOpResult.second.get())->getValue() == 0)
             || (typeid(*(secondOpResult.second)) == typeid(NumberArith) && static_cast<NumberArith*>(secondOpResult.second.get())->getValue() == 1))
        return firstOpResult;
    else {
        return std::make_pair((firstOpResult.first == TypeInfo::NUMBER && secondOpResult.first == TypeInfo::NUMBER ? TypeInfo::NUMBER : TypeInfo::LIST), make_unique<Division>(std::move(firstOpResult.second), std::move(secondOpResult.second)));
    }
}

std::string Division::toString() const
{
    std::string result;
    if (typeid(*first_op) == typeid(Addition) || typeid(*first_op) == typeid(Subtraction))
        result = "(" + first_op->toString() + ")";
    else result = first_op->toString();
    result += "/";
    if (typeid(*second_op) == typeid(Addition) || typeid(*second_op) == typeid(LevelMultiplication) || typeid(*second_op) == typeid(Division) || typeid(*second_op) == typeid(Subtraction)) return result + "(" + second_op->toString() + ")";
    else return result + second_op->toString();
}

bool Division::equals(const AbstractExpression *other) const
{
    if (typeid(*other) != typeid(Division)) return false;
    const Division *casted = static_cast<const Division*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
