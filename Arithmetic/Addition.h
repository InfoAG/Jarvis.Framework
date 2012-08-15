#ifndef ADDITION_H
#define ADDITION_H

#include "AbstractBinaryOperation.h"
#include "NumberArith.h"

namespace CAS {

class Addition : public AbstractBinaryOperation
{
public:
    /**
     * Construct from operands
     * @param first_op
     * @param second_op
     */
    Addition(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return std::unique_ptr<AbstractArithmetic>(new Addition(*this)); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType getType() const { return ADDITION; }
    virtual std::string toString() const { return first_op->toString() + "+" + second_op->toString(); }
};

}

#endif //ADDITION_H
