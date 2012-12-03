#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "AbstractLevelingOperation.h"
#include "NumberValue.h"
#include "Exponentiation.h"
#include "BinaryMultiplication.h"

namespace CAS {

class Addition;
class List;

class LevelMultiplication : public AbstractLevelingOperation
{
private:
    typedef std::vector<std::pair<ExpressionP, ExpressionP>> BasisValues;

    bool returnsNumber;

    void addToBasisValue(BasisValues &values, ExpressionP basis, ExpressionP exponent) const;

public:
    LevelMultiplication(ExpressionP first_op, ExpressionP second_op, bool returnsNumber = false) : AbstractLevelingOperation(std::move(first_op), std::move(second_op)), returnsNumber(returnsNumber) {}
    virtual ExpressionP copy() const { return make_unique<LevelMultiplication>(*this); }
    LevelMultiplication(Operands operands) : AbstractLevelingOperation(std::move(operands)) {}

    virtual ExpressionP eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif //MULTIPLICATION_H
