#ifndef FUNCTIONDEFINITIONSTATEMENT_H
#define FUNCTIONDEFINITIONSTATEMENT_H

#include "AbstractStatement.h"
#include "Scope.h"
#include "FunctionDeclaration.h"
#include "exception/InvalidTreeException.h"

namespace CAS {

class FunctionDefinitionStatement : public AbstractStatement
{
private:
    FunctionDeclaration head;
    StatementP body;

public:
    FunctionDefinitionStatement(FunctionDeclaration head, StatementP body) : head(std::move(head)), body(std::move(body)) {}
    FunctionDefinitionStatement(const FunctionDefinitionStatement &other) : head(other.head), body(other.body->copy()) {}
    virtual StatementP copy() const { return make_unique<FunctionDefinitionStatement>(*this); }
    virtual AbstractExpression::ExpressionP execute(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { return head.toString() + " {\n" + body->toString() + "\n}"; }
    virtual bool equals(const AbstractStatement *other) const { return typeid(*other) == typeid(FunctionDefinitionStatement) && *this == *static_cast<const FunctionDefinitionStatement*>(other); }

    bool operator==(const FunctionDefinitionStatement &other) const { return head == other.head && body->equals(other.body.get()); }
};

}

#endif // FUNCTIONDEFINITIONSTATEMENT_H
