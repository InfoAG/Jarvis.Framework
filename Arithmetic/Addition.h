#ifndef ADDITION_H
#define ADDITION_H

#include "AbstractLevelingOperation.h"
#include "NumberArith.h"
#include "Multiplication.h"
#include <algorithm>

namespace CAS {

class Addition : public AbstractLevelingOperation
{
private:
    typedef std::vector<std::pair<Operands, int> > MonomValues;

    int &accessMonomValue(MonomValues &values, const Operands &monom) const;

public:
    /**
     * Construct from operands
     * @param first_op
     * @param second_op
     */
    Addition(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : AbstractLevelingOperation(std::move(first_op), std::move(second_op)) {}
    Addition(const Operands &operands) : AbstractLevelingOperation(operands) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return std::unique_ptr<AbstractArithmetic>(new Addition(*this)); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType getType() const { return ADDITION; }
    virtual std::string toString() const;
    virtual bool isEqual(const AbstractArithmetic *other) const;
};

}

#endif //ADDITION_H
