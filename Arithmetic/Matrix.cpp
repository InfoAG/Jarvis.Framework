#include "Matrix.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Matrix::eval(const EvalInfo &ei) const
{
    Operands result;
    for (const auto &operand : operands) result.emplace_back(operand->eval(ei));
    return make_unique<Matrix>(std::move(result));
}

std::string Matrix::toString() const
{
    std::string result = "[";
    if (operands.front()->type() == MATRIX)
        for (const auto &operand : operands) result += operand->toString();
    else {
        for (auto it = operands.cbegin(); it != operands.cend() - 1; ++it)
            result += (*it)->toString() + ",";
        result += operands.back()->toString();
    }
    return result + "]";
}

bool Matrix::equals(const AbstractArithmetic *other) const
{
    if (other->type() != MATRIX) return false;
    else return equalOperands(operands, static_cast<const Matrix*>(other)->getOperands());
}

}
