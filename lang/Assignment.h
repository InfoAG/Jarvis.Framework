#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "AbstractBinaryExpression.h"
#include "Variable.h"
#include "Function.h"
#include "LazyEval.h"
#include "VariableDeclaration.h"
#include "exception/InvalidTreeException.h"

namespace CAS {

class Assignment : public AbstractBinaryExpression
{
public:
    /**
     * Construct from operands
     * @param first_op
     * @param second_op
     */
    Assignment(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryExpression(std::move(first_op), std::move(second_op)) {}
    virtual StatementP copy() const { return make_unique<Assignment>(*this); }
    virtual ExpressionP constructWithArgs(ExpressionP first, ExpressionP second) const { return make_unique<Assignment>(std::move(first), std::move(second)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { return first_op->toString() + "=" + second_op->toString(); }
    virtual bool equals(const AbstractStatement *other) const;
    virtual bool isSymbolic(Scope &scope) const { return second_op->isSymbolic(scope); }
};

}

#endif // ASSIGNMENT_H
