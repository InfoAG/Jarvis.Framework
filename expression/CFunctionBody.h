#ifndef CFUNCTIONBODY_H
#define CFUNCTIONBODY_H

#include "AbstractExpression.h"

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

    virtual EvalRes eval(Scope &, const std::function<void(const std::string &)> &, bool , bool ) const { throw "need args"; }
    virtual bool equals(const AbstractExpression *) const { return false; }
    virtual std::string toString() const { return "<loaded from lib>"; }

    virtual EvalRes evalWithArgs(Operands args, Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const {
        auto result = evalFunc(args, scope, load, lazy, direct);
        //Operands a = std::move(args);
        if (result == nullptr)
            return std::make_pair(returnType, make_unique<Function>(identifier, std::move(args)));
        else return std::make_pair(returnType, std::move(result)); }
};

}

#endif // CFUNCTIONBODY_H
