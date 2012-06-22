#ifndef ABSTRACTUNARYOPERATION_H
#define ABSTRACTUNARYOPERATION_H

#include "AbstractArithmetic.h"

namespace CAS {

class AbstractUnaryOperation : public AbstractArithmetic
{
protected:
    std::unique_ptr<AbstractArithmetic> operand;

public:
    inline AbstractUnaryOperation(std::unique_ptr<AbstractArithmetic> operand) : operand(std::move(operand)) {};
    inline AbstractUnaryOperation(const AbstractUnaryOperation &other) : operand(other.operand->copy()) {};
};

}

#endif //ABSTRACTUNARYOPERATION_H
