#ifndef FUNCTION_H
#define FUNCTION_H

#include "AbstractLevelingOperation.h"

namespace CAS {

class Function : public AbstractLevelingOperation
{
private:
    std::string identifier;

public:
    Function(const std::string identifier, Operands arguments) : AbstractLevelingOperation(std::forward<Operands>(arguments)), identifier(identifier) {}
    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<Function>(*this); }

    virtual std::unique_ptr<AbstractExpression> eval(Scope &scope, bool lazy) const;
    virtual bool equals(const AbstractExpression *other) const;
    virtual std::string toString() const;

    std::string getIdentifier() const { return identifier; }
};

}

#endif //FUNCTION_H
