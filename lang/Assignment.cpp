#include "Assignment.h"

namespace CAS {

AbstractExpression::ExpressionP Assignment::executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    auto secondOpResult = second_op->executeExpression(scope.getVar(static_cast<Variable*>(first_op.get())->getIdentifier()).first, load, print, execOption);

    scope.defineVar(static_cast<Variable*>(first_op.get())->getIdentifier(), secondOpResult->copyEx());
    //else if (typeid(*first_op) == typeid(VariableDeclaration))

        /*if (typeid(*first_op) == typeid(Function)) {
        bool assignable = true;
        std::vector<std::string> argStrings;
        for (const auto &op : static_cast<Function*>(first_op.get())->getOperands()) {
            if (typeid(op) != typeid(Variable)) {
                assignable = false;
                break;
            } else argStrings.emplace_back(static_cast<Variable*>(op.get())->getIdentifier());
        }
        if (assignable) {
            scope.assignFunc(std::make_pair(static_cast<Function*>(first_op.get())->getIdentifier(), FunctionDefinition(std::move(argStrings), secondOpResult->copy(), secondOpResult.first)));
        }
    }*/
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
        TypeCollection tc(TypeCollection::all());
        tc.types.erase(TypeInfo::VOID);
        auto secondOpT = second_op->typeCheck(tc, scope);
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
