#ifndef ADDITION_H
#define ADDITION_H

#include "AbstractLevelingOperation.h"
#include "NumberArith.h"
#include "LevelMultiplication.h"
#include "VectorExpression.h"
#include <algorithm>
#include <map>

namespace CAS {

class List;

class Addition : public AbstractLevelingOperation
{
private:
    typedef std::vector<std::pair<std::vector<AbstractExpression*>, double>> MonomValues;

    double &accessMonomValue(MonomValues &values, Operands monom) const;

public:
    /**
     * Construct from operands
     * @param first_op
     * @param second_op
     */
    Addition(ExpressionP first_op, ExpressionP second_op) : AbstractLevelingOperation(std::move(first_op), std::move(second_op)) {}
    Addition(Operands operands) : AbstractLevelingOperation(std::move(operands)) {}
    virtual ExpressionP copy() const { return make_unique<Addition>(*this); }

    virtual EvalRes eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
    //virtual EvalRes directEval() const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif //ADDITION_H
