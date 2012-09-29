#ifndef SCOPEEXPRESSION_H
#define SCOPEEXPRESSION_H

#include "AbstractLevelingOperation.h"
#include "Scope.h"

namespace CAS {

class ScopeExpression : public AbstractLevelingOperation
{
public:
    ScopeExpression(Operands operands) : AbstractLevelingOperation(std::move(operands)) {}
    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<ScopeExpression>(*this); }

    virtual std::unique_ptr<AbstractExpression> eval(Scope &scope, bool lazy) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif // SCOPEEXPRESSION_H
