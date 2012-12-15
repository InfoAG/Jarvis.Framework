#ifndef ABSTRACTBINARYEXPRESSION_H
#define ABSTRACTBINARYEXPRESSION_H

#include "AbstractExpression.h"

namespace CAS {

//! Abstract base class for all binary operations
class AbstractBinaryExpression : public AbstractExpression
{
protected:
    ExpressionP first_op; //!< Pointer to root of the first operand's arithmetical tree
    ExpressionP second_op; //!< Pointer to root of the second operand's arithmetical tree

public:
    /**
     * Construct from operands
     * @param first_op
     * @param second_op
     */
    AbstractBinaryExpression(ExpressionP first_op, ExpressionP second_op) : first_op(std::move(first_op)), second_op(std::move(second_op)) {}
    //! Copy constructor
    AbstractBinaryExpression(const AbstractBinaryExpression &other) : first_op(other.first_op->copyEx()), second_op(other.second_op->copyEx()) {}

    virtual ExpressionP constructWithArgs(ExpressionP first, ExpressionP second) const = 0;

    virtual ExpressionP substituteConstants() const { return constructWithArgs(first_op->substituteConstants(), second_op->substituteConstants()); }
    virtual bool hasVar(const std::string &id) const { return first_op->hasVar(id) || second_op->hasVar(id); }
    virtual bool isSymbolic(Scope &scope) const { return first_op->isSymbolic(scope) || second_op->isSymbolic(scope); }

    ExpressionP &getFirstOp() { return first_op; }
    const ExpressionP &getFirstOp() const { return first_op; }
    ExpressionP &getSecondOp() { return second_op; }
    const ExpressionP &getSecondOp() const { return second_op; }
};

}

#endif //ABSTRACTBINARYEXPRESSION_H
