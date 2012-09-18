#include "Range.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Range::eval(const EvalInfo &ei) const
{
    std::unique_ptr<AbstractArithmetic> startRes = start->eval(ei), endRes = end->eval(ei), stepRes = step->eval(ei);
    if (startRes->type() == NUMBERARITH && endRes->type() == NUMBERARITH && stepRes->type() == NUMBERARITH) {
        Operands result;
        for (Integer i = std::move(static_cast<NumberArith*>(startRes.get())->getValue()); i <= static_cast<NumberArith*>(endRes.get())->getValue(); i += static_cast<NumberArith*>(stepRes.get())->getValue())
            result.emplace_back(make_unique<NumberArith>(std::move(i)));
        return Matrix(std::move(result)).eval(ei);
    } else return make_unique<Range>(std::move(startRes), std::move(endRes), std::move(stepRes));
}

std::string Range::toString() const
{
    std::string result = "range(" + start->toString() + "," + end->toString();
    if (step->type() != NUMBERARITH || static_cast<NumberArith*>(step.get())->getValue() != 1) result += "," + step->toString();
    return result + "]";
}

bool Range::equals(const AbstractArithmetic *other) const
{
    return other->type() == RANGE && start->equals(static_cast<const Range*>(other)->getStart().get()) && end->equals(static_cast<const Range*>(other)->getEnd().get()) && step->equals(static_cast<const Range*>(other)->getStep().get());
}

}
