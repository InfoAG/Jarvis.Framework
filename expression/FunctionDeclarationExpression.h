#ifndef FUNCTIONDECLARATIONEXPRESSION_H
#define FUNCTIONDECLARATIONEXPRESSION_H

#include "AbstractExpression.h"
#include "Scope.h"

namespace CAS {

class FunctionDeclarationExpression : public AbstractExpression
{
private:
    FunctionSignature sig;
    TypeInfo returnType;
    std::vector<std::string> argumentNames;
    /*
    std::string id;
    std::vector<TypeInfo> argumentTypes;
    std::vector<std::string> argumentNames;
    */

public:
    FunctionDeclarationExpression(FunctionSignature sig, TypeInfo returnType, std::vector<std::string> argumentNames) : sig(std::move(sig)), returnType(std::move(returnType)), argumentNames(std::move(argumentNames)) {}
    virtual ExpressionP copy() const { return make_unique<FunctionDeclarationExpression>(*this); }
    virtual ExpressionP execute(Scope &, const std::function<void(const std::string &)> &, ExecOption) const { return copy(); }
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const { return typeid(*other) == typeid(FunctionDeclarationExpression) && *this == *static_cast<const FunctionDeclarationExpression*>(other); }

    const FunctionSignature &getSignature() const { return sig; }
    TypeInfo getReturnType() const { return returnType; }
    const std::vector<std::string> &getArgNames() const { return argumentNames; }

    bool operator==(const FunctionDeclarationExpression &other) const { return returnType == other.returnType && sig == other.sig; }
};

}

#endif // FUNCTIONDECLARATIONEXPRESSION_H
