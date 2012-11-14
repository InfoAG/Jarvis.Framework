#include "RangedForExpression.h"

namespace CAS {

AbstractExpression::EvalRes RangedForExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    auto listRes = list->eval(scope, load, lazy, direct);
    if (((typeid(*declaration) != typeid(VariableDeclarationExpression) || static_cast<VariableDeclarationExpression*>(declaration.get())->getIDs().size() != 1) && typeid(*declaration) != typeid(Variable)) || listRes.first != TypeInfo::LIST) throw "herp";
    else if (typeid(*(listRes.second)) == typeid(List)) {
        std::string varID;
        if (typeid(*declaration) == typeid(Variable))
            varID = static_cast<Variable*>(declaration.get())->getIdentifier();
        else varID = static_cast<VariableDeclarationExpression*>(declaration.get())->getIDs().front();
        Scope forScope(&scope);
        declaration->eval(forScope, load, lazy, direct);
        Operands result;
        for (const auto &item : static_cast<List*>(listRes.second.get())->getOperands()) {
            forScope.defineVar(varID, item->eval(scope, load, lazy, direct));
            result.emplace_back(make_unique<OutputExpression>(instruction->eval(forScope, load, lazy, direct).second));
        }
        return std::make_pair(TypeInfo::VOID, make_unique<MultiLineExpression>(std::move(result)));
    } else return std::make_pair(TypeInfo::VOID, make_unique<RangedForExpression>(declaration->copy(), std::move(listRes.second), instruction->copy()));
}

}
