#ifndef IFEXPRESSION_H
#define IFEXPRESSION_H

#include "AbstractExpression.h"
#include "BoolValue.h"
#include "OutputExpression.h"

namespace CAS {

class IfExpression : public AbstractExpression
{
private:
    std::vector<std::pair<ExpressionP, ExpressionP>> conditionals;

public:
    IfExpression(std::vector<std::pair<ExpressionP, ExpressionP>> conditionals) : conditionals(std::move(conditionals)) {}
    IfExpression(const IfExpression &other);

    virtual ExpressionP copy() const { return make_unique<IfExpression>(*this); }
    virtual EvalRes eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;

    const std::vector<std::pair<ExpressionP, ExpressionP>> &getConditionals() const { return conditionals; }
};

}

#endif // IFEXPRESSION_H
