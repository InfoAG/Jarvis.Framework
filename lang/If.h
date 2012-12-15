#ifndef IF_H
#define IF_H

#include "AbstractStatement.h"
#include "BoolValue.h"
#include "Print.h"

namespace CAS {

class If : public AbstractStatement
{
private:
    std::vector<std::pair<AbstractExpression::ExpressionP, StatementP>> conditionals;

public:
    If(std::vector<std::pair<AbstractExpression::ExpressionP, StatementP>> conditionals) : conditionals(std::move(conditionals)) {}
    If(const If &other);

    virtual StatementP copy() const { return make_unique<If>(*this); }
    virtual AbstractExpression::ExpressionP execute(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const;
    virtual bool equals(const AbstractStatement *other) const;

    const std::vector<std::pair<AbstractExpression::ExpressionP, StatementP>> &getConditionals() const { return conditionals; }
};

}

#endif // IF_H
