#ifndef BOOLVALUE_H
#define BOOLVALUE_H

#include "AbstractExpression.h"

namespace CAS {

class BoolValue : public AbstractExpression
{
private:
    bool value_;

public:
    BoolValue(bool value) : value_(value) {}

    virtual StatementP copy() const { return make_unique<BoolValue>(*this); }
    virtual ExpressionP executeExpression(Scope &, const LoadFunc &, const PrintFunc &, ExecOption) const { return copyEx(); }
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &) { candidates.assertContains(*this, TypeInfo::BOOL); return TypeInfo::BOOL; }
    virtual ExpressionP substituteConstants() const { return copyEx(); }
    virtual std::string toString() const { return value_ ? "true" : "false"; }
    virtual bool equals(const AbstractStatement *other) const;
    virtual bool isValue() const { return true; }
    virtual bool isSymbolic(Scope &) const { return false; }

    bool value() const { return value_; }
};

}

#endif // BOOLVALUE_H
