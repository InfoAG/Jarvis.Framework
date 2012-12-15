#include "AbstractStatement.h"
#include "AbstractExpression.h"

namespace CAS {

std::unique_ptr<AbstractExpression> AbstractStatement::eval(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption)
{
    typeCheck(TypeCollection::all(), scope);
    return execute(scope, load, print, execOption);
}

}
