#include "Modulo.h"

namespace CAS {

AbstractExpression::ExpressionP Modulo::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    auto first_op_result = first_op->eval(scope, load, lazy, direct), second_op_result = second_op->eval(scope, load, lazy, direct);
    if (typeid(*(first_op_result)) == typeid(NumberValue) && typeid(*(second_op_result)) == typeid(NumberValue))
        return make_unique<NumberValue>(*(static_cast<NumberValue*>(first_op_result.get())) % *(static_cast<NumberValue*>(second_op_result.get())));
    else return make_unique<Modulo>(std::move(first_op_result), std::move(second_op_result));
}

TypeInfo Modulo::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (candidates.contains(TypeInfo::NUMBER)) {
        first_op->typeCheck({{TypeInfo::NUMBER}}, scope);
        second_op->typeCheck({{TypeInfo::NUMBER}}, scope);
        return TypeInfo::NUMBER;
    } else throw "typing";
}

std::string Modulo::toString() const
{
    std::string result;
    if (typeid(*first_op) == typeid(Addition) || typeid(*first_op) == typeid(Subtraction) || typeid(*first_op) == typeid(LevelMultiplication) || typeid(*first_op) == typeid(Division) || typeid(*first_op) == typeid(Assignment))
        result = "(" + first_op->toString() + ")";
    else result = first_op->toString();
    result += "%";
    if (typeid(*second_op) == typeid(Addition) || typeid(*second_op) == typeid(Subtraction) || typeid(*second_op) == typeid(LevelMultiplication) || typeid(*second_op) == typeid(Division) || typeid(*second_op) == typeid(Assignment))
        return result + "(" + second_op->toString() + ")";
    else return result + second_op->toString();
}

bool Modulo::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(Modulo) && first_op->equals(static_cast<const Modulo*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const Modulo*>(other)->getSecondOp().get());
}

}
