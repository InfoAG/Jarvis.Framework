#ifndef EXPONENTIATION_H
#define EXPONENTIATION_H

#include "AbstractBinaryExpression.h"
#include "NumberValue.h"
#include "LevelMultiplication.h"
#include "Division.h"
#include "Subtraction.h"
#include "Constant.h"
#include "NaturalLogarithm.h"

namespace CAS {

class Exponentiation : public AbstractBinaryExpression
{
public:
    Exponentiation(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryExpression(std::move(first_op), std::move(second_op)) {}
    virtual StatementP copy() const { return make_unique<Exponentiation>(*this); }
    virtual ExpressionP constructWithArgs(ExpressionP first, ExpressionP second) const { return make_unique<Exponentiation>(std::move(first), std::move(second)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual ExpressionP differentiate(const std::string &var) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractStatement *other) const;
};

}

#endif //EXPONENTIATION_H
