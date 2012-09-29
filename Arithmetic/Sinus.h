#ifndef SINUS_H
#define SINUS_H

#include "AbstractUnaryOperation.h"

namespace CAS {

class Sinus : public AbstractUnaryOperation
{
public:
    Sinus(std::unique_ptr<AbstractExpression> operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<AbstractExpression>(*this); }

    virtual std::unique_ptr<AbstractExpression> eval(Scope &scope, bool lazy) const { return this->copy(); }
    virtual std::string toString() const { return std::string("sin(") + operand->toString() + ")"; }
};

}

#endif //SINUS_H
