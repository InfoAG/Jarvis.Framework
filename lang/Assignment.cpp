#include "Assignment.h"

namespace CAS {

AbstractExpression::ExpressionP Assignment::executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    auto secondOpResult = second_op->executeExpression(scope.getVar(static_cast<Variable*>(first_op.get())->getIdentifier()).first, load, print, execOption);
    scope.defineVar(static_cast<Variable*>(first_op.get())->getIdentifier(), secondOpResult->copyEx());
    return secondOpResult;
}

TypeInfo Assignment::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (typeid(*first_op) != typeid(Variable)) throw InvalidTreeException(toString(), "expected variable to assign to");
    if (scope.hasVar(static_cast<const Variable*>(first_op.get())->getIdentifier())) {
        auto varInfo = scope.getVar(static_cast<const Variable*>(first_op.get())->getIdentifier());
        candidates.assertContains(*this, varInfo.second.type);
        second_op->typeCheck({{varInfo.second.type}}, varInfo.first);
        return varInfo.second.type;
    } else {
        auto secondOpT = second_op->typeCheck(candidates, scope);
        scope.declareVar(secondOpT, static_cast<const Variable*>(first_op.get())->getIdentifier());
        return secondOpT;
    }
}

bool Assignment::equals(const AbstractStatement *other) const
{
    if (typeid(*other) != typeid(Assignment)) return false;
    const Assignment *casted = static_cast<const Assignment*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
