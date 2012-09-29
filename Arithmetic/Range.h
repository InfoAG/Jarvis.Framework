#ifndef RANGE_H
#define RANGE_H

#include "AbstractLevelingOperation.h"
#include "NumberArith.h"
#include "Matrix.h"

namespace CAS {

class Range : public AbstractExpression
{
private:
    std::unique_ptr<AbstractExpression> start;
    std::unique_ptr<AbstractExpression> end;
    std::unique_ptr<AbstractExpression> step;

public:
    Range(std::unique_ptr<AbstractExpression> start, std::unique_ptr<AbstractExpression> end, std::unique_ptr<AbstractExpression> step) : start(std::move(start)), end(std::move(end)), step(std::move(step)) {}
    Range(const Range &other) : start(other.start->copy()), end(other.end->copy()), step(other.step->copy()) {}

    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<Range>(*this); }
    virtual std::unique_ptr<AbstractExpression> eval(Scope &scope, bool lazy) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;

    const std::unique_ptr<AbstractExpression> &getStart() const { return start; }
    const std::unique_ptr<AbstractExpression> &getEnd() const { return end; }
    const std::unique_ptr<AbstractExpression> &getStep() const { return step; }
};

}

#endif // RANGE_H
