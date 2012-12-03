#include "EqualityExpression.h"

namespace CAS {

AbstractExpression::ExpressionP EqualityExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    try {
        auto firstOpResult = first_op->eval(scope, load, lazy, true), secondOpResult = second_op->eval(scope, load, lazy, true);
        return make_unique<BoolValue>(firstOpResult->equals(secondOpResult.get()));
    } catch (const char *s) {
        if (direct) throw s;
        else {
            auto firstOpResult = first_op->eval(scope, load, lazy, false), secondOpResult = second_op->eval(scope, load, lazy, false);
            if (firstOpResult->equals(secondOpResult.get()))
                return make_unique<BoolValue>(true);
            else return make_unique<EqualityExpression>(std::move(firstOpResult), std::move(secondOpResult));
        }
    }
}

TypeInfo EqualityExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (! candidates.contains(TypeInfo::BOOL)) throw "typing";
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

bool EqualityExpression::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(EqualityExpression) && first_op->equals(static_cast<const EqualityExpression*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const EqualityExpression*>(other)->getFirstOp().get());
}

}
