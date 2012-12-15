#ifndef LIST_H
#define LIST_H

#include <vector>
#include "global.h"
#include "AbstractLevelingExpression.h"
#include "Addition.h"
#include "exception/ExecutionException.h"

namespace CAS {

class List : public AbstractLevelingExpression
{
public:
    List(Expressions operands) : AbstractLevelingExpression(std::move(operands)) {}
    List(const List &other) : AbstractLevelingExpression(other) {}
    virtual StatementP copy() const { return make_unique<List>(*this); }
    virtual ExpressionP constructWithArgs(Expressions ops) const { return make_unique<List>(std::move(ops)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const;
    virtual bool equals(const AbstractStatement *other) const;
    virtual bool isValue() const { return true; }
    ExpressionP sum() { return make_unique<Addition>(std::move(operands)); }

    List operator/(const List &other) const;
    List operator/(const NumberValue &other) const;
};

}

#endif // LIST_H
