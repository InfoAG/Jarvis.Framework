#ifndef VARIABLEDECLARATION_H
#define VARIABLEDECLARATION_H

#include "AbstractStatement.h"
#include "Scope.h"
#include "Void.h"

namespace CAS {

class VariableDeclaration : public AbstractStatement
{
private:
    TypeInfo type;
    std::vector<std::string> ids;

public:
    VariableDeclaration(TypeInfo type, std::vector<std::string> ids) : type(std::move(type)), ids(std::move(ids)) {}
    virtual StatementP copy() const { return make_unique<VariableDeclaration>(*this); }

    virtual AbstractExpression::ExpressionP execute(Scope &, const LoadFunc &, const PrintFunc &, ExecOption) const { return make_unique<Void>(); }
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const;
    virtual bool equals(const AbstractStatement *other) const { return typeid(*other) == typeid(VariableDeclaration) && *this == *static_cast<const VariableDeclaration*>(other); }

    TypeInfo getType() const { return type; }
    const std::vector<std::string> &getIDs() const { return ids; }

    bool operator==(const VariableDeclaration &other) const { return type == other.type && ids == other.ids; }
};

}

#endif // VARIABLEDECLARATION_H
