#include "Range.h"

namespace CAS {

std::unique_ptr<AbstractExpression> Range::eval(Scope &scope, bool lazy) const
{
    std::unique_ptr<AbstractExpression> startRes = start->eval(scope, lazy), endRes = end->eval(scope, lazy), stepRes = step->eval(scope, lazy);
    if (typeid(startRes) == typeid(NumberArith) && typeid(endRes) == typeid(NumberArith) && typeid(stepRes) == typeid(NumberArith)) {
        Operands result;
        for (Integer i = std::move(static_cast<NumberArith*>(startRes.get())->getValue()); i <= static_cast<NumberArith*>(endRes.get())->getValue(); i += static_cast<NumberArith*>(stepRes.get())->getValue())
            result.emplace_back(make_unique<NumberArith>(std::move(i)));
        return Matrix(std::move(result)).eval(scope, lazy);
    } else return make_unique<Range>(std::move(startRes), std::move(endRes), std::move(stepRes));
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
