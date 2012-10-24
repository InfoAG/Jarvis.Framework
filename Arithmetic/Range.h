#ifndef RANGE_H
#define RANGE_H

#include "AbstractLevelingOperation.h"
#include "NumberArith.h"
#include "List.h"

namespace CAS {

class Range : public AbstractExpression
{
private:
    ExpressionP start;
    ExpressionP end;
    ExpressionP step;

public:
    Range(ExpressionP start, ExpressionP end, ExpressionP step) : start(std::move(start)), end(std::move(end)), step(std::move(step)) {}
    Range(const Range &other) : start(other.start->copy()), end(other.end->copy()), step(other.step->copy()) {}

    virtual ExpressionP copy() const { return make_unique<Range>(*this); }
    virtual EvalRes eval(Scope &scope, bool lazy) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;

    const ExpressionP &getStart() const { return start; }
    const ExpressionP &getEnd() const { return end; }
    const ExpressionP &getStep() const { return step; }
};

}

#endif // RANGE_H
