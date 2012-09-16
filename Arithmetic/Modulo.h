#ifndef MODULO_H
#define MODULO_H

#include "AbstractBinaryOperation.h"
#include "NumberArith.h"

namespace CAS {

class Modulo : public AbstractBinaryOperation
{
public:
    /**
     * Construct from operands
     * @param first_op
     * @param second_op
     */
    Modulo(std::unique_ptr<AbstractArithmetic> first_op, std::unique_ptr<AbstractArithmetic> second_op) : AbstractBinaryOperation(std::move(first_op), std::move(second_op)) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<Modulo>(*this); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType type() const { return MODULO; }
    virtual std::string toString() const;
    virtual bool equals(const AbstractArithmetic *other) const;
};

}

#endif // MODULO_H
