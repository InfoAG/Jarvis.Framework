#include "Assignment.h"

namespace CAS {

std::unique_ptr<AbstractExpression> Assignment::eval(Scope &scope, bool lazy) const
{
    auto secondOpResult = second_op->eval(scope, lazy);
    if (typeid(*first_op) == typeid(Variable)) scope.assignVar(std::make_pair(static_cast<Variable*>(first_op.get())->getIdentifier(), Definition(secondOpResult->copy(), typeid(*second_op) == typeid(LazyEval) ? false : true)));
    else if (typeid(*first_op) == typeid(Function)) {
        bool assignable = true;
        std::vector<std::string> argStrings;
        for (const auto &op : static_cast<Function*>(first_op.get())->getOperands()) {
            if (typeid(op) != typeid(Variable)) {
                assignable = false;
                break;
            } else argStrings.emplace_back(static_cast<Variable*>(op.get())->getIdentifier());
        }
        if (assignable) {
            scope.assignFunc(std::make_pair(static_cast<Function*>(first_op.get())->getIdentifier(), FunctionDefinition(std::move(argStrings), secondOpResult->copy(), typeid(*second_op) == typeid(LazyEval) ? false : true)));
        }
    }
    return secondOpResult;
}

bool Assignment::equals(const AbstractExpression *other) const
{
    if (typeid(*other) != typeid(Assignment)) return false;
    const Assignment *casted = static_cast<const Assignment*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
