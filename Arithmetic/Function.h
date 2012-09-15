#ifndef FUNCTION_H
#define FUNCTION_H

#include "AbstractLevelingOperation.h"

namespace CAS {

class Function : public AbstractLevelingOperation
{
private:
    std::string identifier;

public:
    Function(const std::string identifier, Operands arguments) : AbstractLevelingOperation(std::forward<Operands>(arguments)), identifier(identifier) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return make_unique<Function>(*this); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType type() const { return FUNCTION; }
    virtual bool equals(const AbstractArithmetic *other) const;
    virtual std::string toString() const;

    std::string getIdentifier() const { return identifier; }
};

}

#endif //FUNCTION_H
