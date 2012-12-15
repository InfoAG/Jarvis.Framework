#ifndef MULTILINE_H
#define MULTILINE_H

#include "AbstractStatement.h"
#include "Scope.h"
#include "Print.h"
#include "Return.h"

namespace CAS {

class MultiLine : public AbstractStatement
{
private:
    Statements operands;

public:
    MultiLine(Statements operands) : operands(std::move(operands)) {}
    MultiLine(const MultiLine &other);
    virtual StatementP copy() const { return make_unique<MultiLine>(*this); }

    virtual AbstractExpression::ExpressionP execute(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const;
    virtual bool equals(const AbstractStatement *other) const;

    const Statements &getOperands() const { return operands; }
};

}

#endif // MULTILINE_H
