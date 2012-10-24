#include "Range.h"

namespace CAS {

AbstractExpression::EvalRes Range::eval(Scope &scope, bool lazy) const
{
    auto startRes = start->eval(scope, lazy), endRes = end->eval(scope, lazy), stepRes = step->eval(scope, lazy);
    if (typeid(*(startRes.second)) == typeid(NumberArith) && typeid(*(endRes.second)) == typeid(NumberArith) && typeid(*(stepRes.second)) == typeid(NumberArith)) {
        Operands result;
        for (Integer i = std::move(static_cast<NumberArith*>(startRes.second.get())->getValue()); i <= static_cast<NumberArith*>(endRes.second.get())->getValue(); i += static_cast<NumberArith*>(stepRes.second.get())->getValue())
            result.emplace_back(make_unique<NumberArith>(std::move(i)));
        return List(std::move(result)).eval(scope, lazy);
    } else return std::make_pair(LIST, make_unique<Range>(std::move(startRes.second), std::move(endRes.second), std::move(stepRes.second)));
}

std::string Range::toString() const
{
    std::string result = "range(" + start->toString() + "," + end->toString();
    if (typeid(step) != typeid(NumberArith) || static_cast<NumberArith*>(step.get())->getValue() != 1) result += "," + step->toString();
    return result + ")";
}

bool Range::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(Range) && start->equals(static_cast<const Range*>(other)->getStart().get()) && end->equals(static_cast<const Range*>(other)->getEnd().get()) && step->equals(static_cast<const Range*>(other)->getStep().get());
}

}
