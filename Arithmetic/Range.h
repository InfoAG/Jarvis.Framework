#ifndef RANGE_H
#define RANGE_H

#include "AbstractLevelingOperation.h"
#include "NumberArith.h"
#include "Matrix.h"

namespace CAS {

class Range : public AbstractArithmetic
{
private:
    std::unique_ptr<AbstractArithmetic> start;
    std::unique_ptr<AbstractArithmetic> end;
    std::unique_ptr<AbstractArithmetic> step;

public:
    Range(std::unique_ptr<AbstractArithmetic> start, std::unique_ptr<AbstractArithmetic> end, std::unique_ptr<AbstractArithmetic> step) : start(std::move(start)), end(std::move(end)), step(std::move(step)) {}
    Range(const Range &other) : start(other.start->copy()), end(other.end->copy()), step(other.step->copy()) {}

    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<Range>(*this); }
    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType type() const { return RANGE; }
    virtual std::string toString() const;
    virtual bool equals(const AbstractArithmetic *other) const;

    const std::unique_ptr<AbstractArithmetic> &getStart() const { return start; }
    const std::unique_ptr<AbstractArithmetic> &getEnd() const { return end; }
    const std::unique_ptr<AbstractArithmetic> &getStep() const { return step; }
};

}

#endif // RANGE_H
