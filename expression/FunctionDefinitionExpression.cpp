#include "FunctionDefinitionExpression.h"

namespace CAS {

AbstractExpression::ExpressionP FunctionDefinitionExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    if (head.getArgNames().empty() && ! head.getSignature().argumentTypes.empty()) throw "gimme names bro";
    if (! scope.hasFunc(head.getSignature())) head.eval(scope, load, lazy, direct);
    scope.defineFunc(head.getSignature(), {body->copy(), head.getArgNames(), head.getReturnType()});
    return copy();
}

TypeInfo FunctionDefinitionExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (candidates.contains(TypeInfo::VOID)) {
        head.typeCheck(TypeCollection::all(), scope);
        body->typeCheck(TypeCollection::all(), bodyScope);
        return TypeInfo::VOID;
    } else throw "typing";
}

}
