#include "LogicalAnd.h"

namespace CAS {

AbstractExpression::ExpressionP LogicalAnd::executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    auto firstOpResult = first_op->executeExpression(scope, load, print, execOption), secondOpResult = second_op->executeExpression(scope, load, print, execOption);
    if (typeid(*(firstOpResult)) == typeid(BoolValue) && typeid(*(secondOpResult)) == typeid(BoolValue))
        return make_unique<BoolValue>(static_cast<BoolValue*>(firstOpResult.get())->value() && static_cast<BoolValue*>(secondOpResult.get())->value());
    else return make_unique<LogicalAnd>(std::move(firstOpResult), std::move(secondOpResult));
}

TypeInfo LogicalAnd::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::BOOL);
    first_op->typeCheck({{TypeInfo::BOOL}}, scope);
    second_op->typeCheck({{TypeInfo::BOOL}}, scope);
    return TypeInfo::BOOL;
}

bool LogicalAnd::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(LogicalAnd) && first_op->equals(static_cast<const LogicalAnd*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const LogicalAnd*>(other)->getFirstOp().get());
}

}
