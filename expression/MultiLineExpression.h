#ifndef MULTILINEEXPRESSION_H
#define MULTILINEEXPRESSION_H

#include "AbstractLevelingOperation.h"
#include "Scope.h"
#include "OutputExpression.h"
#include "ReturnExpression.h"

namespace CAS {

class MultiLineExpression : public AbstractLevelingOperation
{
public:
    MultiLineExpression(Operands operands) : AbstractLevelingOperation(std::move(operands)) {}
    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<MultiLineExpression>(*this); }

    virtual ExpressionP execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif // MULTILINEEXPRESSION_H
