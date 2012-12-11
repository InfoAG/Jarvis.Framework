#ifndef VARIABLE_H
#define VARIABLE_H

#include "AbstractExpression.h"
#include "Scope.h"
#include <string>
#include "exception/ExecutionException.h"
#include "NumberValue.h"

namespace CAS {

class Variable : public AbstractExpression
{
private:
    std::string identifier;

public:
    Variable(const std::string &identifier) : identifier(identifier) {}
    virtual ExpressionP copy() const { return make_unique<Variable>(*this); }

    virtual ExpressionP execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual ExpressionP differentiate(const std::string &var) const;
    virtual std::string toString() const { return identifier; }
    virtual inline bool equals(const AbstractExpression *other) const;
    virtual bool hasVar(const std::string &id) const { return identifier == id; }

    std::string getIdentifier() const { return identifier; }
};

}

#endif //VARIABLE_H
