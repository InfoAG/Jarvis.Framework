#include "Equality.h"

namespace CAS {

AbstractExpression::ExpressionP Equality::executeExpression(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    /*
    try {
        auto firstOpResult = first_op->executeExpression(scope, lazy, true), secondOpResult = second_op->executeExpression(scope, EAGER);
        return make_unique<BoolValue>(firstOpResult->equals(secondOpResult.get()));
    } catch (ExecutionException &e) {
        if (execOption == EAGER || e.reason() != ExecutionException::FAILEDEAGER) throw e;
        else {
            auto firstOpResult = first_op->executeExpression(scope, lazy, false), secondOpResult = second_op->executeExpression(scope, lazy, false);
            if (firstOpResult->equals(secondOpResult.get()))
                return make_unique<BoolValue>(true);
            else return make_unique<Equality>(std::move(firstOpResult), std::move(secondOpResult));
        }
    }
    */
    auto firstOpResult = first_op->executeExpression(scope, load, print, execOption), secondOpResult = second_op->executeExpression(scope, load, print, execOption);
    if (typeid(*firstOpResult) == typeid(BoolValue) && typeid(*secondOpResult) == typeid(BoolValue))
        return make_unique<BoolValue>(static_cast<BoolValue*>(firstOpResult.get())->value() == static_cast<BoolValue*>(secondOpResult.get())->value());
    else if (typeid(*firstOpResult) == typeid(NumberValue) && typeid(*secondOpResult) == typeid(NumberValue))
        return make_unique<BoolValue>(static_cast<NumberValue*>(firstOpResult.get())->getValue() == static_cast<NumberValue*>(secondOpResult.get())->getValue());
    else if (firstOpResult->equals(secondOpResult.get()))
        return make_unique<BoolValue>(true);
    else return make_unique<Equality>(std::move(firstOpResult), std::move(secondOpResult));
}

TypeInfo Equality::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::BOOL);
    TypeCollection opCol{TypeCollection::all()};
    opCol.erase(TypeInfo::VOID);
    try {
        auto firstOpT = first_op->typeCheck(opCol, scope);
        second_op->typeCheck({{firstOpT}}, scope);
        return TypeInfo::BOOL;
    } catch(const char *) {
        auto secondOpT = second_op->typeCheck(opCol, scope);
        first_op->typeCheck({{secondOpT}}, scope);
        return TypeInfo::BOOL;
    }
}

bool Equality::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(Equality) && first_op->equals(static_cast<const Equality*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const Equality*>(other)->getFirstOp().get());
}

}
