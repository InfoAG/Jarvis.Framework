#ifndef NATURALLOGARITHM_H
#define NATURALLOGARITHM_H

#include "AbstractUnaryOperation.h"
#include <cmath>
#include "NumberValue.h"
#include "LevelMultiplication.h"
#include "Division.h"

namespace CAS {

class NaturalLogarithm : public AbstractUnaryOperation
{
public:
    NaturalLogarithm(ExpressionP operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual ExpressionP copy() const { return make_unique<NaturalLogarithm>(*this); }

    virtual ExpressionP execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual ExpressionP differentiate(const std::string &var) const;
    virtual std::string toString() const { return "ln(" + operand->toString() + ")"; }
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif // NATURALLOGARITHM_H
