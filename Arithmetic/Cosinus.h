#ifndef COSINUS_H
#define COSINUS_H

#include "AbstractExpression.h"

namespace CAS {

class Cosinus : public AbstractUnaryOperation
{
public:
    Cosinus(ExpressionP operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual ExpressionP copy() const { return make_unique<ExpressionP>(*this); }

    virtual EvalRes eval(Scope &scope, bool lazy) const { return this->copy(); }
};

}

#endif //COSINUS_H
