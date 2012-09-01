#ifndef SINUS_H
#define SINUS_H

#include "AbstractUnaryOperation.h"

namespace CAS {

class Sinus : public AbstractUnaryOperation
{
public:
    Sinus(std::unique_ptr<AbstractArithmetic> operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<AbstractArithmetic>(*this); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const { return this->copy(); }
    virtual ArithmeticType getType() const { return SINUS; }
    virtual std::string toString() const { return std::string("sin(") + operand->toString() + ")"; }
};

}

#endif //SINUS_H
