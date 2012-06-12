#ifndef ABSTRACTUNARYOPERATION_H
#define ABSTRACTUNARYOPERATION_H

#include "AbstractArithmetic.h"

namespace CAS {

class AbstractUnaryOperation : public AbstractArithmetic
{
private:
    Arithmetic *operand;
};

}

#endif ABSTRACTUNARYOPERATION_H
