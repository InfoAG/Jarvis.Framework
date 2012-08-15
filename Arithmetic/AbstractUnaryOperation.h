#ifndef ABSTRACTUNARYOPERATION_H
#define ABSTRACTUNARYOPERATION_H

#include "AbstractArithmetic.h"

namespace CAS {

/**
 * Abstract base class for all unary operations
 */
class AbstractUnaryOperation : public AbstractArithmetic
{
protected:
    std::unique_ptr<AbstractArithmetic> operand; //!< Pointer to root of the operand's arithmetical tree

public:
    AbstractUnaryOperation(std::unique_ptr<AbstractArithmetic> operand) : operand(std::move(operand)) {}
    AbstractUnaryOperation(const AbstractUnaryOperation &other) : operand(other.operand->copy()) {}
};

}

#endif //ABSTRACTUNARYOPERATION_H
