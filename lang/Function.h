#ifndef FUNCTION_H
#define FUNCTION_H

#include "AbstractLevelingExpression.h"
#include "FunctionScope.h"
#include "List.h"
#include "exception/ExecutionException.h"

namespace CAS {

class Function : public AbstractLevelingExpression
{
private:
    std::string identifier;
    std::vector<TypeInfo> argTypes;

public:
    Function(std::string identifier, Expressions arguments) : AbstractLevelingExpression(std::move(arguments)), identifier(std::move(identifier)) {}
    Function(std::string identifier, Expressions arguments, std::vector<TypeInfo> argTypes) : AbstractLevelingExpression(std::move(arguments)), identifier(std::move(identifier)), argTypes(std::move(argTypes)) {}
    virtual StatementP copy() const { return make_unique<Function>(*this); }
    virtual ExpressionP constructWithArgs(Expressions ops) const { return make_unique<Function>(identifier, std::move(ops), argTypes); }

    virtual ExpressionP executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual bool equals(const AbstractStatement *other) const;
    virtual std::string toString() const;
    virtual bool isSymbolic(Scope &scope) const { return scope.funcIsSymbolic({identifier, argTypes}); }

    std::string getIdentifier() const { return identifier; }
};

}

#endif //FUNCTION_H
