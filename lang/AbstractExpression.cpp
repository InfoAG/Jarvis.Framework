#include "AbstractExpression.h"

namespace CAS {

AbstractExpression::ExpressionP AbstractExpression::execute(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    if (execOption == LAZY || isSymbolic(scope)) return executeExpression(scope, load, print, execOption);
    else return substituteConstants()->executeExpression(scope, load, print, execOption);
}


}
