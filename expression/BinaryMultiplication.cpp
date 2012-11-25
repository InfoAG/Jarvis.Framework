#include "BinaryMultiplication.h"

namespace CAS {

AbstractExpression::EvalRes BinaryMultiplication::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    auto firstOpResult = first_op->eval(scope, load, lazy, direct), secondOpResult = second_op->eval(scope, load, lazy, direct);
    if (firstOpResult.first == TypeInfo::VECTOR && secondOpResult.first == TypeInfo::VECTOR) {
        if (typeid(*(firstOpResult.second)) == typeid(VectorExpression) && typeid(*(secondOpResult.second)) == typeid(VectorExpression)) {
            Operands addOps;
            addOps.emplace_back(make_unique<LevelMultiplication>(std::move(static_cast<VectorExpression*>(firstOpResult.second.get())->getX()), std::move(static_cast<VectorExpression*>(secondOpResult.second.get())->getX())));
            addOps.emplace_back(make_unique<LevelMultiplication>(std::move(static_cast<VectorExpression*>(firstOpResult.second.get())->getY()), std::move(static_cast<VectorExpression*>(secondOpResult.second.get())->getY())));
            addOps.emplace_back(make_unique<LevelMultiplication>(std::move(static_cast<VectorExpression*>(firstOpResult.second.get())->getZ()), std::move(static_cast<VectorExpression*>(secondOpResult.second.get())->getZ())));
            return Addition(std::move(addOps)).eval(scope, load, lazy, direct);
        } else return std::make_pair(TypeInfo::NUMBER, make_unique<BinaryMultiplication>(std::move(firstOpResult.second), std::move(secondOpResult.second)));
    } if ((firstOpResult.first == TypeInfo::VECTOR && secondOpResult.first == TypeInfo::LIST) || (firstOpResult.first == TypeInfo::LIST && secondOpResult.first == TypeInfo::VECTOR))
        throw "typing";
    else return LevelMultiplication(std::move(firstOpResult.second), std::move(secondOpResult.second)).eval(scope, load, lazy, direct);
}

bool BinaryMultiplication::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(BinaryMultiplication) && first_op->equals(static_cast<const BinaryMultiplication*>(other)->getFirstOp().get()) && second_op->equals(static_cast<const BinaryMultiplication*>(other)->getSecondOp().get());
}

}
