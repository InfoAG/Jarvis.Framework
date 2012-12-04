#ifndef OUTPUTEXPRESSION_H
#define OUTPUTEXPRESSION_H

#include "AbstractUnaryOperation.h"

namespace CAS {

class OutputExpression : public AbstractUnaryOperation
{
public:
    OutputExpression() {};
    OutputExpression(ExpressionP operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual ExpressionP copy() const { return make_unique<OutputExpression>(*this); }

    virtual ExpressionP execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const { return make_unique<OutputExpression>(operand->execute(scope, load, execOption)); }
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { if (operand == nullptr) return std::string(); else return operand->toString(); }
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif // OUTPUTEXPRESSION_H
