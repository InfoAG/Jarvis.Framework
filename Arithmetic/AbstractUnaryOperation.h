#ifndef ABSTRACTUNARYOPERATION_H
#define ABSTRACTUNARYOPERATION_H

#include "AbstractExpression.h"

namespace CAS {

/**
 * Abstract base class for all unary operations
 */
class AbstractUnaryOperation : public AbstractExpression
{
protected:
    ExpressionP operand; //!< Pointer to root of the operand's arithmetical tree

public:
    AbstractUnaryOperation(ExpressionP operand) : operand(std::move(operand)) {}
    AbstractUnaryOperation(const AbstractUnaryOperation &other) : operand(other.operand->copy()) {}

    const ExpressionP &getOperand() const { return operand; }
    ExpressionP &getOperand() { return operand; }
};

}

#endif //ABSTRACTUNARYOPERATION_H
