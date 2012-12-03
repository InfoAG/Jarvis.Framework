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
    std::function<ExpressionP(const Operands &, Scope &, const std::function<void(const std::string &)> &, bool, bool)> evalFunc;

public:
    CFunctionBody(TypeInfo returnType, std::string identifier, std::function<ExpressionP(const Operands &, Scope &, const std::function<void(const std::string &)> &, bool, bool)> evalFunc) : returnType(std::move(returnType)), identifier(std::move(identifier)), evalFunc(std::move(evalFunc)) {}
    virtual ExpressionP copy() const { return make_unique<CFunctionBody>(*this); }

    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &) { if (candidates.contains(returnType)) return returnType;  else throw "typing"; }
    virtual ExpressionP eval(Scope &, const std::function<void(const std::string &)> &, bool , bool ) const { throw "need args"; }
    virtual bool equals(const AbstractExpression *) const { return false; }
    virtual std::string toString() const { return "<loaded from lib>"; }

    virtual ExpressionP evalWithArgs(Operands args, Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
};

}

#endif // CFUNCTIONBODY_H
