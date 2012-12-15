#include "Import.h"

namespace CAS {

AbstractExpression::ExpressionP Import::execute(Scope &, const LoadFunc &load, const PrintFunc &, ExecOption) const
{
    load(fileName);
    return make_unique<Void>();
}

bool Import::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(Import) && fileName == static_cast<const Import*>(other)->getFileName();
}

}
