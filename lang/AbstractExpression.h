#ifndef ABSTRACTEXPRESSION_H
#define ABSTRACTEXPRESSION_H

#include "AbstractStatement.h"

namespace CAS {

class AbstractExpression : public AbstractStatement
{
public:
    typedef std::unique_ptr<AbstractExpression> ExpressionP;
    typedef std::vector<ExpressionP> Expressions;

    virtual ExpressionP copyEx() const { return ExpressionP(static_cast<AbstractExpression*>(copy().release())); }

    virtual ExpressionP execute(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption = STD) const;

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption = STD) const = 0;
    virtual ExpressionP substituteConstants() const { throw InvalidTreeException(toString(), "cannot call substituteConstants() on \"" + toString() + "\""); }
    virtual ExpressionP differentiate(const std::string &) const { throw InvalidTreeException(toString(), "cannot differentiate \"" + toString() + "\""); }
    virtual bool isValue() const { return false; }
    virtual bool hasVar(const std::string &) const { throw InvalidTreeException(toString(), "cannot call hasVar() on \"" + toString() + "\""); }
    virtual bool isSymbolic(Scope &) const { throw InvalidTreeException(toString(), "cannot call isSymbolic() on \"" + toString() + "\""); }
};

}

#endif // ABSTRACTEXPRESSION_H
