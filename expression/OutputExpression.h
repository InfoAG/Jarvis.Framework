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

    virtual EvalRes eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const { return std::make_pair(TypeInfo::VOID, make_unique<OutputExpression>(operand->eval(scope, load, lazy, direct).second)); }
    virtual std::string toString() const { if (operand == nullptr) return std::string(); else return operand->toString(); }
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif // OUTPUTEXPRESSION_H
