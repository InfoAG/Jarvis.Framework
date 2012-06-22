#ifndef ABSTRACTBINARYOPERATION_H
#define ABSTRACTBINARYOPERATION_H

#include "AbstractArithmetic.h"

namespace CAS {

class AbstractBinaryOperation : public AbstractArithmetic
{
protected:
    std::unique_ptr<AbstractArithmetic> first_op;
    std::unique_ptr<AbstractArithmetic> second_op;

public:
    inline AbstractBinaryOperation(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : first_op(std::move(first_op)), second_op(std::move(second_op)) {};
    inline AbstractBinaryOperation(const AbstractBinaryOperation &other) : first_op(other.first_op->copy()), second_op(other.second_op->copy()) {};
};

}

#endif //ABSTRACTBINARYOPERATION_H
