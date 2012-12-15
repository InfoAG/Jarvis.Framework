#ifndef ABSTRACTUNARYEXPRESSION_H
#define ABSTRACTUNARYEXPRESSION_H

#include "AbstractExpression.h"

namespace CAS {

/**
 * Abstract base class for all unary operations
 */
class AbstractUnaryExpression : public AbstractExpression
{
protected:
    ExpressionP operand; //!< Pointer to root of the operand's arithmetical tree

public:
    AbstractUnaryExpression(ExpressionP operand) : operand(std::move(operand)) {}
    AbstractUnaryExpression(const AbstractUnaryExpression &other) : operand(other.operand->copyEx()) {}
    virtual ExpressionP constructWithArgs(ExpressionP op) const = 0;

    virtual ExpressionP substituteConstants() const { return constructWithArgs(operand->substituteConstants()); }
    virtual bool hasVar(const std::string &id) const { return operand->hasVar(id); }
    virtual bool isSymbolic(Scope &scope) const { return operand->isSymbolic(scope); }

    const ExpressionP &getOperand() const { return operand; }
    ExpressionP &getOperand() { return operand; }

    bool operator==(const AbstractUnaryExpression &other) const { return operand->equals(other.operand.get()); }
};

}

#endif //ABSTRACTUNARYEXPRESSION_H
