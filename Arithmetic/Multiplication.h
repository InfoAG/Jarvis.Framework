#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "AbstractBinaryOperation.h"
#include "NumberArith.h"

namespace CAS {

class Multiplication : public AbstractBinaryOperation
{
public:
    inline Multiplication(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {};
    virtual inline std::unique_ptr<AbstractArithmetic> copy() const { return std::unique_ptr<AbstractArithmetic>(new Multiplication(*this)); };

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual inline ArithmeticType getType() const { return MULTIPLICATION; };
    virtual inline std::string getString() const { return first_op->getString() + "*" + second_op->getString(); };
};

}

#endif //MULTIPLICATION_H
