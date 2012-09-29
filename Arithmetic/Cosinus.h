#ifndef COSINUS_H
#define COSINUS_H

#include "AbstractExpression.h"

namespace CAS {

class Cosinus : public AbstractUnaryOperation
{
public:
    Cosinus(std::unique_ptr<AbstractExpression> operand) : AbstractUnaryOperation(std::move(operand)) {}
    virtual std::unique_ptr<AbstractExpression> copy() const { return make_unique<AbstractExpression>(*this); }

    virtual std::unique_ptr<AbstractExpression> eval(Scope &scope, bool lazy) const { return this->copy(); }
};

}

#endif //COSINUS_H
