#ifndef EXPONENTIATION_H
#define EXPONENTIATION_H

#include "AbstractBinaryOperation.h"
#include "NumberArith.h"
#include "LevelMultiplication.h"
#include "Division.h"
#include "Subtraction.h"

namespace CAS {

class Exponentiation : public AbstractBinaryOperation
{
public:
    Exponentiation(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual ExpressionP copy() const { return make_unique<Exponentiation>(*this); }

    virtual EvalRes eval(Scope &scope, bool lazy) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif //EXPONENTIATION_H
