#ifndef VARIABLE_H
#define VARIABLE_H

#include "AbstractExpression.h"
#include <string>

namespace CAS {

class Variable : public AbstractExpression
{
private:
    std::string identifier;

public:
    Variable(const std::string &identifier) : identifier(identifier) {}
    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<Variable>(*this); }

    virtual std::unique_ptr<AbstractExpression> eval(Scope &scope, bool lazy) const;
    virtual std::string toString() const { return identifier; }
    virtual inline bool equals(const AbstractExpression *other) const;
    std::string getIdentifier() const { return identifier; }
};

}

#endif //VARIABLE_H
