#ifndef VOID_H
#define VOID_H

#include "AbstractExpression.h"

namespace CAS {

class Void : public AbstractExpression
{
public:
    virtual StatementP copy() const { return make_unique<Void>(*this); }

    virtual ExpressionP executeExpression(Scope &, const LoadFunc &, const PrintFunc &, ExecOption) const { return make_unique<Void>(); }
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &) { candidates.assertContains(*this, TypeInfo::VOID); return TypeInfo::VOID; }
    virtual std::string toString() const { return "VOID"; }
    virtual bool equals(const AbstractStatement *other) const { return typeid(*other) == typeid(Void); }
};

}

#endif // VOID_H
