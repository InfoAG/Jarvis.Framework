#include "VariableDeclarationExpression.h"

namespace CAS {

AbstractExpression::EvalRes VariableDeclarationExpression::eval(Scope &scope, const std::function<void(const std::string &)> &, bool, bool) const
{
    for (const auto &id : ids) scope.declareVar(type, id);
    return std::make_pair(TypeInfo::VOID, copy());
}

std::string VariableDeclarationExpression::toString() const
{
    std::string result = type.toString() + " " + ids.front();
    for (auto it = ids.cbegin() + 1; it != ids.cend(); ++it) result += ", " + *it;
    return result;
}

}
