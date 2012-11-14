#include "ImportExpression.h"

namespace CAS {

AbstractExpression::EvalRes ImportExpression::eval(Scope &, const std::function<void(const std::string &)> &load, bool, bool) const
{
    load(fileName);
    return std::make_pair(TypeInfo::VOID, make_unique<OutputExpression>());
}

bool ImportExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(ImportExpression) && fileName == static_cast<const ImportExpression*>(other)->getFileName();
}

}
