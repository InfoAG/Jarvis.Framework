#include "Matrix.h"

namespace CAS {

std::unique_ptr<AbstractExpression> Matrix::eval(Scope &scope, bool lazy) const
{
    Operands result;
    for (const auto &operand : operands) result.emplace_back(operand->eval(scope, lazy));
    if (result.size() == 1) return std::move(result.front());
    else return make_unique<Matrix>(std::move(result));
}

std::string Matrix::toString() const
{
    std::string result = "[";
    if (typeid(operands.front()) == typeid(Matrix))
        for (const auto &operand : operands) result += operand->toString();
    else {
        for (auto it = operands.cbegin(); it != operands.cend() - 1; ++it)
            result += (*it)->toString() + ",";
        result += operands.back()->toString();
    }
    return result + "]";
}

bool Matrix::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(Matrix) && equalOperands(operands, static_cast<const Matrix*>(other)->getOperands());
}

}
