#ifndef DIVISION_H
#define DIVISION_H

#include "AbstractBinaryOperation.h"
#include "NumberValue.h"
#include "Addition.h"
#include "Subtraction.h"
#include "LevelMultiplication.h"

namespace CAS {

class Division : public AbstractBinaryOperation
{
public:
    Division(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual ExpressionP copy() const { return make_unique<Division>(*this); }

    virtual ExpressionP execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual ExpressionP differentiate(const std::string &) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif //DIVISION_H
