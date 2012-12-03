#ifndef EXPONENTIATION_H
#define EXPONENTIATION_H

#include "AbstractBinaryOperation.h"
#include "NumberValue.h"
#include "LevelMultiplication.h"
#include "Division.h"
#include "Subtraction.h"

namespace CAS {

class Exponentiation : public AbstractBinaryOperation
{
public:
    Exponentiation(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual ExpressionP copy() const { return make_unique<Exponentiation>(*this); }

    virtual ExpressionP eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif //EXPONENTIATION_H
