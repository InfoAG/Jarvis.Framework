#include "FunctionDefinitionExpression.h"

namespace CAS {

AbstractExpression::ExpressionP FunctionDefinitionExpression::execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const
{
    if (! scope.hasFunc(head.getSignature())) head.execute(scope, load, execOption);
    scope.defineFunc(head.getSignature(), head.getArgNames(), body->copy());
    return copy();
}

TypeInfo FunctionDefinitionExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (head.getArgNames().empty() && ! head.getSignature().argumentTypes.empty()) throw InvalidTreeException(toString(), "function head is missing argument names.");
    candidates.assertContains(*this, TypeInfo::VOID);
    head.typeCheck(TypeCollection::all(), scope);
    body->typeCheck(TypeCollection::all(), bodyScope);
    return TypeInfo::VOID;
}

}
