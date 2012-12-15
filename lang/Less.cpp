#include "Less.h"

namespace CAS {

AbstractExpression::ExpressionP Less::executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    auto firstOpResult = first_op->executeExpression(scope, load, print, execOption), secondOpResult = second_op->executeExpression(scope, load, print, execOption);
    if (typeid(*(firstOpResult)) == typeid(NumberValue) && typeid(*(secondOpResult)) == typeid(NumberValue))
        return make_unique<BoolValue>(static_cast<NumberValue*>(firstOpResult.get())->getValue() < static_cast<NumberValue*>(secondOpResult.get())->getValue());
    else return make_unique<Less>(std::move(firstOpResult), std::move(secondOpResult));
}

TypeInfo Less::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::BOOL);
    TypeCollection opCol{TypeCollection::all()};
    opCol.erase(TypeInfo::VOID);
    try {
        second_op->typeCheck({{first_op->typeCheck(opCol, scope)}}, scope);
        return TypeInfo::BOOL;
    } catch (UndecidableTypeException &) {
        first_op->typeCheck({{second_op->typeCheck(opCol, scope)}}, scope);
        return TypeInfo::BOOL;
    }
}

bool Less::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(Less) && first_op->equals(static_cast<const Less*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const Less*>(other)->getFirstOp().get());
}

}
