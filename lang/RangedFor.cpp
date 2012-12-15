#include "RangedFor.h"

namespace CAS {

AbstractExpression::ExpressionP RangedFor::execute(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    auto listRes = list->execute(scope, load, print, EAGER);
    std::string varID;
    if (typeid(*declaration) == typeid(Variable))
        varID = static_cast<Variable*>(declaration.get())->getIdentifier();
    else varID = static_cast<VariableDeclaration*>(declaration.get())->getIDs().front();
    Scope forScope(&scope);
    declaration->execute(forScope, load, print, execOption);
    for (const auto &item : static_cast<List*>(listRes.get())->getOperands()) {
        forScope.defineVar(varID, item->execute(scope, load, print, execOption));
        instruction->execute(forScope, load, print, execOption);
    }
    return make_unique<Void>();
}

TypeInfo RangedFor::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if ((typeid(*declaration) != typeid(VariableDeclaration) || static_cast<VariableDeclaration*>(declaration.get())->getIDs().size() != 1) && typeid(*declaration) != typeid(Variable))
        throw InvalidTreeException(toString(), "expected variable declaration in ranged for loop");
    else {
        candidates.assertContains(*this, TypeInfo::VOID);
        list->typeCheck({{{TypeInfo::LIST, static_cast<VariableDeclaration*>(declaration.get())->getType()}}}, scope);
        return TypeInfo::VOID;
    }
}

}
