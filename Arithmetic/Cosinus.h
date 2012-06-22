#ifndef COSINUS_H
#define COSINUS_H

#include "AbstractArithmetic.h"

namespace CAS {

class Cosinus : public AbstractUnaryOperation
{
public:
    inline Cosinus(std::unique_ptr<AbstractArithmetic> operand) : AbstractUnaryOperation(std::move(operand)) {};
    virtual inline std::unique_ptr<AbstractArithmetic> copy() const { return std::unique_ptr<AbstractArithmetic>(new Cosinus(*this); };

    virtual inline std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const { return this->copy(); };
    virtual inline ArithmeticType getType() const { return COSINUS; };
};

}

#endif //COSINUS_H
