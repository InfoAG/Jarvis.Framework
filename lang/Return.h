#ifndef RETURN_H
#define RETURN_H

#include "AbstractStatement.h"
#include "AbstractExpression.h"
#include "Void.h"
#include "ReturnExpression.h"

namespace CAS {

class Return : public AbstractStatement
{
private:
    AbstractExpression::ExpressionP expression;

public:
    Return(AbstractExpression::ExpressionP expression) : expression(std::move(expression)) {}
    Return(const Return &other) : expression(other.expression->copyEx()) {}
    virtual StatementP copy() const { return make_unique<Return>(*this); }

    virtual AbstractExpression::ExpressionP execute(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { return "return " + expression->toString(); }
    virtual bool equals(const AbstractStatement *other) const;

    const AbstractExpression::ExpressionP &getExpression() const { return expression; }
};

}

#endif // RETURN_H
