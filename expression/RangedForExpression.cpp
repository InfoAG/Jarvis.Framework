#include "RangedForExpression.h"

namespace CAS {

AbstractExpression::ExpressionP RangedForExpression::execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const
{
    auto listRes = list->execute(scope, load, execOption);
    if (typeid(*(listRes)) == typeid(List)) {
        std::string varID;
        if (typeid(*declaration) == typeid(Variable))
            varID = static_cast<Variable*>(declaration.get())->getIdentifier();
        else varID = static_cast<VariableDeclarationExpression*>(declaration.get())->getIDs().front();
        Scope forScope(&scope);
        declaration->execute(forScope, load, execOption);
        Operands result;
        for (const auto &item : static_cast<List*>(listRes.get())->getOperands()) {
            forScope.defineVar(varID, item->execute(scope, load, execOption));
            result.emplace_back(make_unique<OutputExpression>(instruction->execute(forScope, load, execOption)));
        }
        return make_unique<MultiLineExpression>(std::move(result));
    } else return make_unique<RangedForExpression>(declaration->copy(), std::move(listRes), instruction->copy());
}

TypeInfo RangedForExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (( typeid(*declaration) != typeid(VariableDeclarationExpression) || static_cast<VariableDeclarationExpression*>(declaration.get())->getIDs().size() != 1) && typeid(*declaration) != typeid(Variable))
        throw InvalidTreeException(toString(), "expected variable declaration in ranged for loop");
    else {
        candidates.assertContains(*this, TypeInfo::VOID);
        list->typeCheck(TypeCollection::allLists(), scope);
        return TypeInfo::VOID;
    }
}

}
