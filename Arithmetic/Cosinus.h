#ifndef COSINUS_H
#define COSINUS_H

#include "AbstractArithmetic.h"

namespace CAS {

class Cosinus : public AbstractUnaryOperation
{
public:
    Cosinus(std::unique_ptr<AbstractArithmetic> operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<AbstractArithmetic>(*this); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const { return this->copy(); }
    virtual ArithmeticType type() const { return COSINUS; }
};

}

#endif //COSINUS_H
