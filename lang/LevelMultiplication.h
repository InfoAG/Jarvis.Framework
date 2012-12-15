#ifndef LEVELMULTIPLICATION_H
#define LEVELMULTIPLICATION_H

#include "AbstractLevelingExpression.h"
#include "NumberValue.h"
#include "Exponentiation.h"
#include "BinaryMultiplication.h"

namespace CAS {

class Addition;
class List;

class LevelMultiplication : public AbstractLevelingExpression
{
private:
    typedef std::vector<std::pair<ExpressionP, ExpressionP>> BasisValues;

    bool returnsNumber;

    void addToBasisValue(BasisValues &values, ExpressionP basis, ExpressionP exponent) const;

public:
    LevelMultiplication(ExpressionP first_op, ExpressionP second_op, bool returnsNumber = false) : AbstractLevelingExpression(std::move(first_op), std::move(second_op)), returnsNumber(returnsNumber) {}
    LevelMultiplication(Expressions operands) : AbstractLevelingExpression(std::move(operands)) {}
    virtual StatementP copy() const { return make_unique<LevelMultiplication>(*this); }
    virtual ExpressionP constructWithArgs(Expressions ops) const { return make_unique<LevelMultiplication>(std::move(ops)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual ExpressionP differentiate(const std::string &var) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractStatement *other) const;
};

}

#endif // LEVELMULTIPLICATION_H
