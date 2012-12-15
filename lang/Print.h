#ifndef PRINT_H
#define PRINT_H

#include "AbstractUnaryExpression.h"
#include "Void.h"

namespace CAS {

class Print : public AbstractStatement
{
private:
    AbstractExpression::ExpressionP expression;

public:
    Print() {}
    Print(AbstractExpression::ExpressionP expression) : expression(std::move(expression)) {}
    Print(const Print &other) : expression(other.expression->copyEx()) {}
    virtual StatementP copy() const { return make_unique<Print>(*this); }

    virtual AbstractExpression::ExpressionP execute(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { if (expression == nullptr) return std::string(); else return expression->toString(); }
    virtual bool equals(const AbstractStatement *other) const;

    const AbstractExpression::ExpressionP &getExpression() const { return expression; }
};

}

#endif // PRINT_H
