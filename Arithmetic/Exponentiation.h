#ifndef EXPONENTIATION_H
#define EXPONENTIATION_H

#include "AbstractBinaryOperation.h"
#include "NumberArith.h"
#include "Multiplication.h"
#include "Division.h"
#include "Subtraction.h"

namespace CAS {

class Exponentiation : public AbstractBinaryOperation
{
public:
    Exponentiation(std::unique_ptr<AbstractExpression> first_op, std::unique_ptr<AbstractExpression> second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<Exponentiation>(*this); }

    virtual std::unique_ptr<AbstractExpression> eval(Scope &scope, bool lazy) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif //EXPONENTIATION_H
