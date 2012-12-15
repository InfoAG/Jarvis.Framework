#ifndef NATURALLOGARITHM_H
#define NATURALLOGARITHM_H

#include "AbstractUnaryExpression.h"
#include <cmath>
#include "NumberValue.h"
#include "LevelMultiplication.h"
#include "Division.h"

namespace CAS {

class NaturalLogarithm : public AbstractUnaryExpression
{
public:
    NaturalLogarithm(ExpressionP operand) : AbstractUnaryExpression(std::move(operand)) {}
    virtual StatementP copy() const { return make_unique<NaturalLogarithm>(*this); }
    virtual ExpressionP constructWithArgs(ExpressionP op) const { return make_unique<NaturalLogarithm>(std::move(op)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual ExpressionP differentiate(const std::string &var) const;
    virtual std::string toString() const { return "ln(" + operand->toString() + ")"; }
    virtual bool equals(const AbstractStatement *other) const;
};

}

#endif // NATURALLOGARITHM_H
