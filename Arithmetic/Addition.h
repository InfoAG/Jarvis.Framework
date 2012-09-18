#ifndef ADDITION_H
#define ADDITION_H

#include "AbstractLevelingOperation.h"
#include "NumberArith.h"
#include "Multiplication.h"
#include "Matrix.h"
#include <algorithm>

namespace CAS {

class Addition : public AbstractLevelingOperation
{
private:
    typedef std::vector<std::pair<std::vector<AbstractArithmetic*>, Integer>> MonomValues;

    Integer &accessMonomValue(MonomValues &values, Operands monom) const;

public:
    /**
     * Construct from operands
     * @param first_op
     * @param second_op
     */
    Addition(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : AbstractLevelingOperation(std::move(first_op), std::move(second_op)) {}
    Addition(Operands operands) : AbstractLevelingOperation(std::move(operands)) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<Addition>(*this); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType type() const { return ADDITION; }
    virtual std::string toString() const;
    virtual bool equals(const AbstractArithmetic *other) const;
};

}

#endif //ADDITION_H
