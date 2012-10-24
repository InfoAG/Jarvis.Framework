#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "AbstractBinaryOperation.h"
#include "Variable.h"
#include "Function.h"
#include "LazyEval.h"

namespace CAS {

class Assignment : public AbstractBinaryOperation
{
public:
    /**
     * Construct from operands
     * @param first_op
     * @param second_op
     */
    Assignment(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual ExpressionP copy() const { return make_unique<Assignment>(*this); }

    virtual EvalRes eval(Scope &scope, bool lazy) const;
    virtual std::string toString() const { return first_op->toString() + "=" + second_op->toString(); }
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif // ASSIGNMENT_H
