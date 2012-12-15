#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "AbstractBinaryExpression.h"
#include "NumberValue.h"
#include "Addition.h"

namespace CAS {

class Subtraction : public AbstractBinaryExpression
{
public:
    Subtraction(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryExpression(std::move(first_op), std::move(second_op)) {}
    virtual StatementP copy() const { return make_unique<Subtraction>(*this); }
    virtual ExpressionP constructWithArgs(ExpressionP first, ExpressionP second) const { return make_unique<Subtraction>(std::move(first), std::move(second)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const;
    virtual bool equals(const AbstractStatement *other) const;
};

}

#endif //SUBTRACTION_H
