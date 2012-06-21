#ifndef ABSTRACTUNARYOPERATION_H
#define ABSTRACTUNARYOPERATION_H

#include "AbstractArithmetic.h"

namespace CAS {

class AbstractUnaryOperation : public AbstractArithmetic
{
protected:
    AbstractArithmetic *operand;

public:
    inline AbstractUnaryOperation(AbstractArithmetic *operand) : operand(operand) {};
};

}

#endif ABSTRACTUNARYOPERATION_H
