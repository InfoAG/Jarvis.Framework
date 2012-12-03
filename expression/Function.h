#ifndef FUNCTION_H
#define FUNCTION_H

#include "AbstractLevelingOperation.h"
#include "Scope.h"
#include "List.h"

namespace CAS {

class Function : public AbstractLevelingOperation
{
private:
    std::string identifier;
    std::vector<TypeInfo> argTypes;

public:
    Function(std::string identifier, Operands arguments) : AbstractLevelingOperation(std::move(arguments)), identifier(std::move(identifier)) {}
    virtual ExpressionP copy() const { return make_unique<Function>(*this); }

    virtual ExpressionP eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual bool equals(const AbstractExpression *other) const;
    virtual std::string toString() const;

    std::string getIdentifier() const { return identifier; }
};

}

#endif //FUNCTION_H
