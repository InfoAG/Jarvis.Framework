#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "global.h"
#include "AbstractLevelingOperation.h"

namespace CAS {

class Matrix : public AbstractLevelingOperation
{
public:
    Matrix(Operands operands) : AbstractLevelingOperation(std::move(operands)) {}
    Matrix(const Matrix &other) : AbstractLevelingOperation(other) {}

    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<Matrix>(*this); }
    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType type() const { return MATRIX; }
    virtual std::string toString() const;
    virtual bool equals(const AbstractArithmetic *other) const;
};

}

#endif //MATRIX_H
