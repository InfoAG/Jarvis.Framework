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

    virtual ExpressionP copy() const { return make_unique<BoolValue>(*this); }
    virtual ExpressionP execute(Scope &, const std::function<void(const std::string &)> &, ExecOption) const { return copy(); }
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &) { candidates.assertContains(*this, TypeInfo::BOOL); return TypeInfo::BOOL; }
    virtual std::string toString() const { return value_ ? "true" : "false"; }
    virtual bool equals(const AbstractExpression *other) const;
    virtual bool isValue() const { return true; }

    bool value() const { return value_; }
};

}

#endif // BOOLVALUE_H
