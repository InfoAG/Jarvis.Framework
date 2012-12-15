#include "Print.h"

namespace CAS {

AbstractExpression::ExpressionP Print::execute(Scope &scope, const AbstractStatement::LoadFunc &load, const AbstractStatement::PrintFunc &print, AbstractStatement::ExecOption execOption) const
{
    print(expression->execute(scope, load, print, execOption)->toString());
    return make_unique<Void>();
}

TypeInfo Print::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::VOID);
    expression->typeCheck(TypeCollection::all(), scope);
    return TypeInfo::VOID;
}

bool Print::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(Print) && expression->equals(static_cast<const Print*>(other)->getExpression().get());
}

}
