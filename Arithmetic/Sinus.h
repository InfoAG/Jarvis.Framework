#ifndef SINUS_H
#define SINUS_H

#include "AbstractUnaryOperation.h"

namespace CAS {

class Sinus : public AbstractUnaryOperation
{
public:
    Sinus(ExpressionP operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual ExpressionP copy() const { return make_unique<ExpressionP>(*this); }

    virtual EvalRes eval(Scope &scope, bool lazy) const { return this->copy(); }
    virtual std::string toString() const { return std::string("sin(") + operand->toString() + ")"; }
};

}

#endif //SINUS_H
