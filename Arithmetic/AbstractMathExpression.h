#ifndef ABSTRACTMATHEXPRESSION_H
#define ABSTRACTMATHEXPRESSION_H

#include "AbstractExpression.h"

namespace CAS {

class AbstractMathExpression : public AbstractExpression
{
public:

    virtual ExpressionP copy() const = 0;
    virtual ReturnType type() const = 0;
};

}

#endif // ABSTRACTMATHEXPRESSION_H
