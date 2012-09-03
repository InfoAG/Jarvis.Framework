#ifndef ABSTRACTBINARYOPERATION_H
#define ABSTRACTBINARYOPERATION_H

#include "AbstractArithmetic.h"

namespace CAS {

//! Abstract base class for all binary operations
class AbstractBinaryOperation : public AbstractArithmetic
{
protected:
    std::unique_ptr<AbstractArithmetic> first_op; //!< Pointer to root of the first operand's arithmetical tree
    std::unique_ptr<AbstractArithmetic> second_op; //!< Pointer to root of the second operand's arithmetical tree

public:
    /**
     * Construct from operands
     * @param first_op
     * @param second_op
     */
    AbstractBinaryOperation(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : first_op(std::move(first_op)), second_op(std::move(second_op)) {}
    //! Copy constructor
    AbstractBinaryOperation(const AbstractBinaryOperation &other) : first_op(other.first_op->copy()), second_op(other.second_op->copy()) {}

    inline std::unique_ptr<AbstractArithmetic> &getFirstOp() { return first_op; }
    inline const std::unique_ptr<AbstractArithmetic> &getFirstOp() const { return first_op; }
    inline std::unique_ptr<AbstractArithmetic> &getSecondOp() { return second_op; }
    inline const std::unique_ptr<AbstractArithmetic> &getSecondOp() const { return second_op; }
};

}

#endif //ABSTRACTBINARYOPERATION_H
