#include "Assignment.h"

namespace CAS {

AbstractExpression::ExpressionP Assignment::execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const
{
    auto secondOpResult = second_op->execute(scope, load, execOption);

    if (typeid(*second_op) == typeid(LazyEval))
        scope.defineVar(static_cast<Variable*>(first_op.get())->getIdentifier(), secondOpResult->copy());
    else scope.defineVar(static_cast<Variable*>(first_op.get())->getIdentifier(), secondOpResult->copy());
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
        auto varT = scope.getVar(static_cast<const Variable*>(first_op.get())->getIdentifier()).second.type;
        candidates.assertContains(*this, varT);
        second_op->typeCheck({{varT}}, scope);
        return varT;
    } else {
        TypeCollection tc(TypeCollection::all());
        tc.types.erase(TypeInfo::VOID);
        auto secondOpT = second_op->typeCheck(tc, scope);
        scope.declareVar(secondOpT, static_cast<const Variable*>(first_op.get())->getIdentifier());
        return secondOpT;
    }
}

bool Assignment::equals(const AbstractExpression *other) const
{
    if (typeid(*other) != typeid(Assignment)) return false;
    const Assignment *casted = static_cast<const Assignment*>(other);
    return first_op->equals(casted->getFirstOp().get()) && second_op->equals(casted->getSecondOp().get());
}

}
