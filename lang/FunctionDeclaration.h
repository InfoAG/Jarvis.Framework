#ifndef FUNCTIONDECLARATION_H
#define FUNCTIONDECLARATION_H

#include "AbstractStatement.h"
#include "Scope.h"
#include "Void.h"

namespace CAS {

class FunctionDeclaration : public AbstractStatement
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
    FunctionDeclaration(FunctionSignature sig, TypeInfo returnType, std::vector<std::string> argumentNames) : sig(std::move(sig)), returnType(std::move(returnType)), argumentNames(std::move(argumentNames)) {}
    virtual StatementP copy() const { return make_unique<FunctionDeclaration>(*this); }
    virtual AbstractExpression::ExpressionP execute(Scope &, const LoadFunc &, const PrintFunc &, ExecOption) const { return make_unique<Void>(); }
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const;
    virtual bool equals(const AbstractStatement *other) const { return typeid(*other) == typeid(FunctionDeclaration) && *this == *static_cast<const FunctionDeclaration*>(other); }

    const FunctionSignature &getSignature() const { return sig; }
    TypeInfo getReturnType() const { return returnType; }
    const std::vector<std::string> &getArgNames() const { return argumentNames; }

    bool operator==(const FunctionDeclaration &other) const { return returnType == other.returnType && sig == other.sig; }
};

}

#endif // FUNCTIONDECLARATION_H
