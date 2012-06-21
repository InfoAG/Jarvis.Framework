#ifndef ABSTRACTBINARYOPERATION_H
#define ABSTRACTBINARYOPERATION_H

#include "AbstractArithmetic.h"

namespace CAS {

class AbstractBinaryOperation : public AbstractArithmetic
{
protected:
    AbstractArithmetic *first_op;
    AbstractArithmetic *second_op;

public:
    inline AbstractBinaryOperation(AbstractArithmetic *first_op, AbstractArithmetic *second_op) : first_op(first_op), second_op(second_op) {};
};

}

#endif //ABSTRACTBINARYOPERATION_H
