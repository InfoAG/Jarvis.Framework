#ifndef NEGATIONEXPRESSION_H
#define NEGATIONEXPRESSION_H

#include "AbstractUnaryOperation.h"
#include "BoolValue.h"

namespace CAS {

class NegationExpression : public AbstractUnaryOperation
{
public:
    NegationExpression(ExpressionP operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual ExpressionP copy() const { return make_unique<NegationExpression>(*this); }

    virtual ExpressionP eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { return "!" + operand->toString(); }
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif // NEGATIONEXPRESSION_H
