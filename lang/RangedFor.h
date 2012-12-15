#ifndef RANGEDFOR_H
#define RANGEDFOR_H

#include "AbstractStatement.h"
#include "Scope.h"
#include "VariableDeclaration.h"
#include "List.h"
#include "Print.h"
#include "Variable.h"
#include "MultiLine.h"
#include "exception/InvalidTreeException.h"

namespace CAS {

class RangedFor : public AbstractStatement
{
private:
    StatementP declaration;
    AbstractExpression::ExpressionP list;
    StatementP instruction;

public:
    RangedFor(StatementP declaration, AbstractExpression::ExpressionP list, StatementP instruction) : declaration(std::move(declaration)), list(std::move(list)), instruction(std::move(instruction)) {}
    RangedFor(const RangedFor &other) : declaration(other.declaration->copy()), list(other.list->copyEx()), instruction(other.instruction->copy()) {}

    virtual StatementP copy() const { return make_unique<RangedFor>(*this); }
    virtual AbstractExpression::ExpressionP execute(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope);
    virtual std::string toString() const { return "for (" + declaration->toString() + " : " + list->toString() + ")\n" + instruction->toString(); }
    virtual bool equals(const AbstractStatement *other) const { return typeid(*other) == typeid(RangedFor) && *this == *static_cast<const RangedFor*>(other); }

    const StatementP &getDeclaration() const { return declaration; }
    const AbstractExpression::ExpressionP &getList() const { return list; }
    const StatementP &getInstruction() const { return instruction; }

    bool operator==(const RangedFor &other) const { return declaration->equals(other.declaration.get()) && list->equals(other.list.get()) && instruction->equals(other.instruction.get()); }
};

}

#endif // RANGEDFOR_H
