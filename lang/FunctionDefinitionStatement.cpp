#include "FunctionDefinitionStatement.h"

namespace CAS {

AbstractExpression::ExpressionP FunctionDefinitionStatement::execute(Scope &scope, const LoadFunc &, const PrintFunc &, ExecOption) const
{
    scope.defineFunc(head.getSignature(), head.getArgNames(), body->copy());
    return make_unique<Void>();
}

TypeInfo FunctionDefinitionStatement::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (head.getArgNames().empty() && ! head.getSignature().argumentTypes.empty()) throw InvalidTreeException(toString(), "function head is missing argument names.");
    candidates.assertContains(*this, TypeInfo::VOID);
    head.typeCheck(TypeCollection::all(), scope);

    Scope::VarDefs args;
    auto itNames = head.getArgNames().cbegin();
    for (const auto &type : head.getSignature().argumentTypes)
        args.insert(std::make_pair(*(itNames++), VariableDefinition{type}));

    Scope bodyScope(&scope, std::move(args));
    body->typeCheck(TypeCollection::all(), bodyScope);
    return TypeInfo::VOID;
}

}
