#ifndef CFUNCTIONBODY_H
#define CFUNCTIONBODY_H

#include "AbstractStatement.h"
#include "Function.h"

namespace CAS {

class Function;

class CFunctionBody : public AbstractStatement
{
private:
    TypeInfo returnType;
    std::string identifier;
    std::function<AbstractExpression::ExpressionP(const AbstractExpression::Expressions &, Scope &, const LoadFunc &, const PrintFunc &, ExecOption)> execFunc;

public:
    CFunctionBody(TypeInfo returnType, std::string identifier, std::function<AbstractExpression::ExpressionP(const AbstractExpression::Expressions &, Scope &, const LoadFunc &, const PrintFunc &, ExecOption)> execFunc) : returnType(std::move(returnType)), identifier(std::move(identifier)), execFunc(std::move(execFunc)) {}
    virtual StatementP copy() const { return make_unique<CFunctionBody>(*this); }

    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &) { candidates.assertContains(*this, returnType); return returnType; }
    virtual AbstractExpression::ExpressionP execute(Scope &, const LoadFunc &, const PrintFunc &, ExecOption) const { throw ExecutionException::noCFuncArgs(toString()); }
    virtual bool equals(const AbstractStatement *) const { return false; }
    virtual std::string toString() const { return "<loaded from lib>"; }

    virtual AbstractExpression::ExpressionP executeWithArgs(const AbstractExpression::Expressions &args, Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const { return execFunc(args, scope, load, print, execOption); }
};

}

#endif // CFUNCTIONBODY_H
