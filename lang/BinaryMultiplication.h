#ifndef BINARYMULTIPLICATON_H
#define BINARYMULTIPLICATON_H

#include "AbstractBinaryExpression.h"
#include "Vector.h"
#include "Addition.h"

namespace CAS {

class LevelMultiplication;

class BinaryMultiplication : public AbstractBinaryExpression
{
private:
    enum {
        UNCHECKED,
        SCALARVECTOR,
        LEVEL,
        LEVELNUM
    } type = UNCHECKED;

public:
    BinaryMultiplication(ExpressionP first_op, ExpressionP second_op) : AbstractBinaryExpression(std::move(first_op), std::move(second_op)) {}
    virtual StatementP copy() const { return make_unique<BinaryMultiplication>(*this); }
    virtual ExpressionP constructWithArgs(ExpressionP first, ExpressionP second) const { return make_unique<BinaryMultiplication>(std::move(first), std::move(second)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual ExpressionP differentiate(const std::string &var) const;
    virtual std::string toString() const { return first_op->toString() + "*" + second_op->toString(); }
    virtual bool equals(const AbstractStatement *other) const;
};

}

#endif // BINARYMULTIPLICATON_H
