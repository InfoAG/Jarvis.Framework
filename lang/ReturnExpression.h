#ifndef RETURNEXPRESSION_H
#define RETURNEXPRESSION_H

#include "AbstractExpression.h"

namespace CAS {

class ReturnExpression : public AbstractExpression
{
private:
    AbstractExpression::ExpressionP expression;

public:
    ReturnExpression(AbstractExpression::ExpressionP expression) : expression(std::move(expression)) {}
    ReturnExpression(const ReturnExpression &other) : expression(other.expression->copyEx()) {}

    virtual StatementP copy() const { return make_unique<ReturnExpression>(*this); }
    virtual ExpressionP executeExpression(Scope &, const LoadFunc &, const PrintFunc &, ExecOption) const { throw InvalidTreeException("", "cannot call executeExpression() on \"ReturnExpression\""); }
    virtual TypeInfo typeCheck(const TypeCollection &, Scope &) { throw InvalidTreeException("", "cannot call typeCheck() on \"ReturnExpression\""); }
    virtual ExpressionP substituteConstants() const { throw InvalidTreeException("", "cannot call substituteConstants() on \"ReturnExpression\""); }
    virtual std::string toString() const { throw InvalidTreeException("", "cannot call toString() on \"ReturnExpression\""); }
    virtual bool equals(const AbstractStatement *other) const { return typeid(*other) == typeid(ReturnExpression); }
    virtual bool isValue() const { throw InvalidTreeException("", "cannot call isValue() on \"ReturnExpression\""); }
    virtual bool isSymbolic(Scope &) const { throw InvalidTreeException("", "cannot call isSymbolic() on \"ReturnExpression\""); }

    const AbstractExpression::ExpressionP &getExpression() const { return expression; }
    AbstractExpression::ExpressionP &getExpression() { return expression; }
};

}

#endif // RETURNEXPRESSION_H
