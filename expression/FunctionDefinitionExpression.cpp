#include "FunctionDefinitionExpression.h"

namespace CAS {

AbstractExpression::EvalRes FunctionDefinitionExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    if (head.getArgNames().empty() && ! head.getSignature().argumentTypes.empty()) throw "gimme names bro";
    if (! scope.hasFunc(head.getSignature())) head.eval(scope, load, lazy, direct);
    scope.defineFunc(head.getSignature(), {body->copy(), head.getArgNames(), head.getReturnType()});
    return std::make_pair(TypeInfo::VOID, copy());
}

}
