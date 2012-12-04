#ifndef FUNCTIONDEFINITIONEXPRESSION_H
#define FUNCTIONDEFINITIONEXPRESSION_H

#include "AbstractExpression.h"
#include "Scope.h"
#include "FunctionDeclarationExpression.h"
#include "exception/InvalidTreeException.h"

namespace CAS {

class FunctionDefinitionExpression : public AbstractExpression
{
private:
    FunctionDeclarationExpression head;
    ExpressionP body;
    Scope bodyScope;

public:
    FunctionDefinitionExpression(FunctionDeclarationExpression head, ExpressionP body) : head(std::move(head)), body(std::move(body)) {}
    FunctionDefinitionExpression(const FunctionDefinitionExpression &other) : head(other.head), body(other.body->copy()) {}
    virtual ExpressionP copy() const { return make_unique<FunctionDefinitionExpression>(*this); }
    virtual ExpressionP execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { return head.toString() + " {\n" + body->toString() + "\n}"; }
    virtual bool equals(const AbstractExpression *other) const { return typeid(*other) == typeid(FunctionDefinitionExpression) && *this == *static_cast<const FunctionDefinitionExpression*>(other); }

    bool operator==(const FunctionDefinitionExpression &other) const { return head == other.head && body->equals(other.body.get()); }
};

}

#endif // FUNCTIONDEFINITIONEXPRESSION_H
