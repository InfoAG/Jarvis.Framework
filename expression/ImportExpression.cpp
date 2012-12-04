#include "ImportExpression.h"

namespace CAS {

AbstractExpression::ExpressionP ImportExpression::execute(Scope &, const std::function<void(const std::string &)> &load, ExecOption) const
{
    load(fileName);
    return make_unique<OutputExpression>();
}

bool ImportExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(ImportExpression) && fileName == static_cast<const ImportExpression*>(other)->getFileName();
}

}
