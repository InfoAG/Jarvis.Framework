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
    inline AbstractBinaryOperation(const AbstractBinaryOperation &other) : first_op(other.first_op->copy()), second_op(other.second_op->copy()) {};
};

}

#endif //ABSTRACTBINARYOPERATION_H
