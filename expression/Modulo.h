#ifndef MODULO_H
#define MODULO_H

#include "AbstractBinaryOperation.h"
#include "NumberValue.h"
#include "Addition.h"
#include "Subtraction.h"
#include "LevelMultiplication.h"
#include "Division.h"
#include "Assignment.h"

namespace CAS {

class Modulo : public AbstractBinaryOperation
{
public:
    /**
     * Construct from operands
     * @param first_op
     * @param second_op
     */
    Modulo(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual ExpressionP copy() const { return make_unique<Modulo>(*this); }

    virtual ExpressionP eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif // MODULO_H
