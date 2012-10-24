#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "global.h"
#include "AbstractLevelingOperation.h"

namespace CAS {

class List : public AbstractLevelingOperation
{
public:
    List(Operands operands) : AbstractLevelingOperation(std::move(operands)) {}
    List(const List &other) : AbstractLevelingOperation(other) {}

    virtual ExpressionP copy() const { return make_unique<List>(*this); }
    virtual EvalRes eval(Scope &scope, bool lazy) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;
};

}

#endif //MATRIX_H
