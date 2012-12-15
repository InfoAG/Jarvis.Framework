#ifndef MODULO_H
#define MODULO_H

#include "AbstractBinaryExpression.h"
#include "NumberValue.h"
#include "Addition.h"
#include "Subtraction.h"
#include "LevelMultiplication.h"
#include "Division.h"
#include "Assignment.h"

namespace CAS {

class Modulo : public AbstractBinaryExpression
{
public:
    /**
     * Construct from operands
     * @param first_op
     * @param second_op
     */
    Modulo(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryExpression(std::move(first_op), std::move(second_op)) {}
    virtual StatementP copy() const { return make_unique<Modulo>(*this); }
    virtual ExpressionP constructWithArgs(ExpressionP first, ExpressionP second) const { return make_unique<Modulo>(std::move(first), std::move(second)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const;
    virtual bool equals(const AbstractStatement *other) const;
};

}

#endif // MODULO_H
