#ifndef CFUNCTIONBODY_H
#define CFUNCTIONBODY_H

#include "AbstractExpression.h"
#include "Function.h"

namespace CAS {

class Function;

class CFunctionBody : public AbstractExpression
{
private:
    TypeInfo returnType;
    std::string identifier;
    std::function<ExpressionP(const Operands &, Scope &, const std::function<void(const std::string &)> &, ExecOption)> execFunc;

public:
    CFunctionBody(TypeInfo returnType, std::string identifier, std::function<ExpressionP(const Operands &, Scope &, const std::function<void(const std::string &)> &, ExecOption)> execFunc) : returnType(std::move(returnType)), identifier(std::move(identifier)), execFunc(std::move(execFunc)) {}
    virtual ExpressionP copy() const { return make_unique<CFunctionBody>(*this); }

    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &) { candidates.assertContains(*this, returnType); return returnType; }
    virtual ExpressionP execute(Scope &, const std::function<void(const std::string &)> &, ExecOption) const { throw ExecutionException::noCFuncArgs(toString()); }
    virtual bool equals(const AbstractExpression *) const { return false; }
    virtual std::string toString() const { return "<loaded from lib>"; }

    virtual ExpressionP executeWithArgs(const Operands &args, Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const { return execFunc(args, scope, load, execOption); }
};

}

#endif // CFUNCTIONBODY_H
