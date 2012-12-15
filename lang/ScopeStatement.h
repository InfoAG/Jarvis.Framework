#ifndef SCOPESTATEMENT_H
#define SCOPESTATEMENT_H

#include "AbstractStatement.h"
#include "Scope.h"
#include "Print.h"

namespace CAS {

class ScopeStatement : public AbstractStatement
{
private:
    StatementP operand;
    Scope myScope;

public:
    ScopeStatement(StatementP operand) : operand(std::move(operand)) {}
    ScopeStatement(const ScopeStatement &other) : operand(other.operand->copy()) {}
    virtual StatementP copy() const { return make_unique<ScopeStatement>(*this); }

    virtual AbstractExpression::ExpressionP execute(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &);
    virtual std::string toString() const { return "{" + operand->toString() + "}"; }
    virtual bool equals(const AbstractStatement *other) const;

    const StatementP &getOperand() const { return operand; }
};

}

#endif // SCOPESTATEMENT_H
