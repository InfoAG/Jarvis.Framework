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
    AbstractUnaryOperation() {}
    AbstractUnaryOperation(ExpressionP operand) : operand(std::move(operand)) {}
    AbstractUnaryOperation(const AbstractUnaryOperation &other) : operand(other.operand->copy()) {}

    virtual bool hasVar(const std::string &id) const { return operand->hasVar(id); }

    const ExpressionP &getOperand() const { return operand; }
    ExpressionP &getOperand() { return operand; }

    bool operator==(const AbstractUnaryOperation &other) const { return operand->equals(other.operand.get()); }
};

}

#endif //ABSTRACTUNARYOPERATION_H
