#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "AbstractLevelingOperation.h"
#include "NumberArith.h"
#include "Exponentiation.h"
#include "Addition.h"

namespace CAS {

class LevelMultiplication : public AbstractLevelingOperation
{
private:
    typedef std::vector<std::pair<ExpressionP, ExpressionP>> BasisValues;

    void addToBasisValue(BasisValues &values, ExpressionP basis, ExpressionP exponent) const;

public:
    LevelMultiplication(ExpressionP first_op, ExpressionP second_op) : AbstractLevelingOperation(std::move(first_op), std::move(second_op)) {}
    virtual ExpressionP copy() const { return make_unique<LevelMultiplication>(*this); }
    LevelMultiplication(Operands operands) : AbstractLevelingOperation(std::move(operands)) {}

    virtual EvalRes eval(Scope &scope, bool lazy) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif //MULTIPLICATION_H
