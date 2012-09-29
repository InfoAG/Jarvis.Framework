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
    std::unique_ptr<AbstractExpression> operand; //!< Pointer to root of the operand's arithmetical tree

public:
    AbstractUnaryOperation(std::unique_ptr<AbstractExpression> operand) : operand(std::move(operand)) {}
    AbstractUnaryOperation(const AbstractUnaryOperation &other) : operand(other.operand->copy()) {}

    const std::unique_ptr<AbstractExpression> &getOperand() const { return operand; }
    std::unique_ptr<AbstractExpression> &getOperand() { return operand; }
};

}

#endif //ABSTRACTUNARYOPERATION_H
