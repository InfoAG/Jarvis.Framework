#include "VariableDeclarationExpression.h"

namespace CAS {

TypeInfo VariableDeclarationExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (candidates.contains(TypeInfo::VOID)) {
        for (const auto &id : ids) scope.declareVar(type, id);
        return TypeInfo::VOID;
    } else throw "typing";
}

std::string VariableDeclarationExpression::toString() const
{
    std::string result = type.toString() + " " + ids.front();
    for (auto it = ids.cbegin() + 1; it != ids.cend(); ++it) result += ", " + *it;
    return result;
}

}
