#include "ScopeStatement.h"

namespace CAS {

AbstractExpression::ExpressionP ScopeStatement::execute(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    Scope evalScope(myScope);
    evalScope.setParent(&scope);
    operand->execute(evalScope, load, print, execOption);
    return make_unique<Void>();
}

bool ScopeStatement::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(ScopeStatement) && operand->equals(static_cast<const ScopeStatement*>(other)->getOperand().get());
}

TypeInfo ScopeStatement::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::VOID);
    myScope.setParent(&scope);
    operand->typeCheck(TypeCollection::all(), myScope);
    return TypeInfo::VOID;
}

}
