#ifndef SINUS_H
#define SINUS_H

#include "AbstractUnaryOperation.h"

namespace CAS {

class Sinus : public AbstractUnaryOperation
{
public:
    inline Sinus(std::unique_ptr<AbstractArithmetic> operand) : AbstractUnaryOperation(std::move(operand)) {};
    virtual inline std::unique_ptr<AbstractArithmetic> copy() const { return std::unique_ptr<AbstractArithmetic>(new Sinus(*this)); };

    virtual inline std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const { return this->copy(); };
    virtual inline ArithmeticType getType() const { return SINUS; };
    virtual inline std::string getString() const { return std::string("sin(") + operand->getString() + ")"; };
};

}

#endif //SINUS_H
