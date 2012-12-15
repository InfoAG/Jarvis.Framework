#ifndef DIVISION_H
#define DIVISION_H

#include "AbstractBinaryExpression.h"
#include "NumberValue.h"
#include "Addition.h"
#include "Subtraction.h"
#include "LevelMultiplication.h"

namespace CAS {

class Division : public AbstractBinaryExpression
{
public:
    Division(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryExpression(std::move(first_op), std::move(second_op)) {}
    virtual StatementP copy() const { return make_unique<Division>(*this); }
    virtual ExpressionP constructWithArgs(ExpressionP first, ExpressionP second) const { return make_unique<Division>(std::move(first), std::move(second)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual ExpressionP differentiate(const std::string &) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractStatement *other) const;
};

}

#endif //DIVISION_H
