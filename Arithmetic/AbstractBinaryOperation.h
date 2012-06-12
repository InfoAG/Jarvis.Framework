#ifndef ABSTRACTBINARYOPERATION_H
#define ABSTRACTBINARYOPERATION_H

#include "AbstractArithmetic.h"

namespace CAS {

class AbstractBinaryOperation : public AbstractArithmetic
{
private:
    AbstractArithmetic *first_op;
    AbstractArithmetic *second_op;
};

}

#endif //ABSTRACTBINARYOPERATION_H
