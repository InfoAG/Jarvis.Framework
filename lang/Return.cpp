#include "Return.h"

namespace CAS {

AbstractExpression::ExpressionP Return::execute(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    expression->execute(scope, load, print, execOption);
    return make_unique<Void>();
}

TypeInfo Return::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::VOID);
    TypeCollection tc(candidates);
    tc.types.erase(TypeInfo::VOID);
    expression->typeCheck(tc, scope);
    return TypeInfo::VOID;
}

bool Return::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(Return) && expression->equals(static_cast<const Return*>(other)->getExpression().get());
}

}
