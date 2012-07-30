#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include "AbstractBinaryOperation.h"

namespace CAS {

class Subtraction : public AbstractBinaryOperation
{
public:
    inline Subtraction(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {};
    virtual inline std::unique_ptr<AbstractArithmetic> copy() const { return std::unique_ptr<AbstractArithmetic>new Subtraction(*this); };

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual inline ArithmeticType getType() const { return Subtraction; };
};

}

#endif //SUBTRACTION_H
