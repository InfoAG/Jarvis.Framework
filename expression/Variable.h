#ifndef VARIABLE_H
#define VARIABLE_H

#include "AbstractExpression.h"
#include "Scope.h"
#include <string>

namespace CAS {

class Variable : public AbstractExpression
{
private:
    std::string identifier;

public:
    Variable(const std::string &identifier) : identifier(identifier) {}
    virtual ExpressionP copy() const { return make_unique<Variable>(*this); }

    virtual ExpressionP eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { return identifier; }
    virtual inline bool equals(const AbstractExpression *other) const;

    std::string getIdentifier() const { return identifier; }
};

}

#endif //VARIABLE_H
