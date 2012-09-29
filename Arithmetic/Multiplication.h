#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include "AbstractLevelingOperation.h"
#include "NumberArith.h"
#include "Exponentiation.h"
#include "Addition.h"

namespace CAS {

class Multiplication : public AbstractLevelingOperation
{
private:
    typedef std::vector<std::pair<std::unique_ptr<AbstractExpression>, std::unique_ptr<AbstractExpression>>> BasisValues;

    void addToBasisValue(BasisValues &values, std::unique_ptr<AbstractExpression> basis, std::unique_ptr<AbstractExpression> exponent) const;

public:
    Multiplication(std::unique_ptr<AbstractExpression> first_op, std::unique_ptr<AbstractExpression> second_op) : AbstractLevelingOperation(std::move(first_op), std::move(second_op)) {}
    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<Multiplication>(*this); }
    Multiplication(Operands operands) : AbstractLevelingOperation(std::move(operands)) {}

    virtual std::unique_ptr<AbstractExpression> eval(Scope &scope, bool lazy) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif //MULTIPLICATION_H
