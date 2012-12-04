#ifndef VARIABLEDECLARATIONEXPRESSION_H
#define VARIABLEDECLARATIONEXPRESSION_H

#include "AbstractLevelingOperation.h"
#include "Scope.h"

namespace CAS {

class VariableDeclarationExpression : public AbstractLevelingOperation
{
private:
    TypeInfo type;
    std::vector<std::string> ids;

public:
    VariableDeclarationExpression(TypeInfo type, std::vector<std::string> ids) : type(std::move(type)), ids(std::move(ids)) {}
    virtual ExpressionP copy() const { return make_unique<VariableDeclarationExpression>(*this); }
    virtual ExpressionP execute(Scope &, const std::function<void(const std::string &)> &, ExecOption) const { return copy(); }
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const { return typeid(*other) == typeid(VariableDeclarationExpression) && *this == *static_cast<const VariableDeclarationExpression*>(other); }

    TypeInfo getType() const { return type; }
    const std::vector<std::string> &getIDs() const { return ids; }

    bool operator==(const VariableDeclarationExpression &other) const { return type == other.type && ids == other.ids; }
};

}

#endif // VARIABLEDECLARATIONEXPRESSION_H
