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
    virtual EvalRes eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const;
    virtual std::string toString() const;
    virtual bool equals(const AbstractExpression *other) const;
    virtual bool isValue() const { return true; }
};

}

#endif //MATRIX_H
