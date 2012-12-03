#ifndef RANGEDFOREXPRESSION_H
#define RANGEDFOREXPRESSION_H

#include "AbstractExpression.h"
#include "Scope.h"
#include "VariableDeclarationExpression.h"
#include "List.h"
#include "OutputExpression.h"
#include "Variable.h"
#include "MultiLineExpression.h"

namespace CAS {

class RangedForExpression : public AbstractExpression
{
private:
    ExpressionP declaration;
    ExpressionP list;
    ExpressionP instruction;

public:
    RangedForExpression(ExpressionP declaration, ExpressionP list, ExpressionP instruction) : declaration(std::move(declaration)), list(std::move(list)), instruction(std::move(instruction)) {}
    RangedForExpression(const RangedForExpression &other) : declaration(other.declaration->copy()), list(other.list->copy()), instruction(other.instruction->copy()) {}

    virtual ExpressionP copy() const { return make_unique<RangedForExpression>(*this); }
    virtual ExpressionP eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { return "for (" + declaration->toString() + " : " + list->toString() + ")\n" + instruction->toString(); }
    virtual bool equals(const AbstractExpression *other) const { return typeid(*other) == typeid(RangedForExpression) && *this == *static_cast<const RangedForExpression*>(other); }

    const ExpressionP &getDeclaration() const { return declaration; }
    const ExpressionP &getList() const { return list; }
    const ExpressionP &getInstruction() const { return instruction; }

    bool operator==(const RangedForExpression &other) const { return declaration->equals(other.declaration.get()) && list->equals(other.list.get()) && instruction->equals(other.instruction.get()); }
};

}

#endif // RANGEDFOREXPRESSION_H
