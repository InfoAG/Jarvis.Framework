#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "AbstractBinaryOperation.h"

namespace CAS {

class Assignment : public AbstractBinaryOperation
{
public:
    /**
     * Construct from operands
     * @param first_op
     * @param second_op
     */
    Assignment(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return std::unique_ptr<AbstractArithmetic>(new Assignment(*this)); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType getType() const { return ASSIGNMENT; }
    virtual std::string toString() const { return first_op->toString() + "=" + second_op->toString(); }
    virtual bool isEqual(const AbstractArithmetic *other) const;
};

}

#endif // ASSIGNMENT_H
