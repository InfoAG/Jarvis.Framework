#ifndef ABSTRACTBINARYOPERATION_H
#define ABSTRACTBINARYOPERATION_H

#include "AbstractExpression.h"

namespace CAS {

//! Abstract base class for all binary operations
class AbstractBinaryOperation : public AbstractExpression
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
    AbstractBinaryOperation(ExpressionP first_op, ExpressionP second_op) : first_op(std::move(first_op)), second_op(std::move(second_op)) {}
    //! Copy constructor
    AbstractBinaryOperation(const AbstractBinaryOperation &other) : first_op(other.first_op->copy()), second_op(other.second_op->copy()) {}

    virtual bool hasVar(const std::string &id) const { return first_op->hasVar(id) || second_op->hasVar(id); }

    ExpressionP &getFirstOp() { return first_op; }
    const ExpressionP &getFirstOp() const { return first_op; }
    ExpressionP &getSecondOp() { return second_op; }
    const ExpressionP &getSecondOp() const { return second_op; }
};

}

#endif //ABSTRACTBINARYOPERATION_H
