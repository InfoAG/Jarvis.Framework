#ifndef ADDITION_H
#define ADDITION_H

#include "AbstractLevelingExpression.h"
#include "NumberValue.h"
#include "LevelMultiplication.h"
#include "Vector.h"
#include <algorithm>
#include <map>
#include "exception/UndecidableTypeException.h"

namespace CAS {

class List;

class Addition : public AbstractLevelingExpression
{
private:
    typedef std::vector<std::pair<std::vector<AbstractExpression*>, double>> MonomValues;

    double &accessMonomValue(MonomValues &values, Expressions monom) const;

public:
    /**
     * Construct from operands
     * @param first_op
     * @param second_op
     */
    Addition(ExpressionP first_op, ExpressionP second_op) : AbstractLevelingExpression(std::move(first_op), std::move(second_op)) {}
    Addition(Expressions operands) : AbstractLevelingExpression(std::move(operands)) {}
    virtual StatementP copy() const { return make_unique<Addition>(*this); }
    virtual ExpressionP constructWithArgs(Expressions ops) const { return make_unique<Addition>(std::move(ops)); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual ExpressionP differentiate(const std::string &var) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractStatement *other) const;
};

}

#endif //ADDITION_H
