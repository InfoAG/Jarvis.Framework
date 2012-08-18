#ifndef FUNCTION_H
#define FUNCTION_H

#include "AbstractLevelingOperation.h"

namespace CAS {

class Function : public AbstractLevelingOperation
{
private:
    std::string identifier;

public:
    Function(const std::string identifier, const Operands &arguments) : AbstractLevelingOperation(arguments), identifier(identifier) {}
    Function(const Operands &operands) : AbstractLevelingOperation(operands) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return std::unique_ptr<AbstractArithmetic>(new Function(*this)); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType getType() const { return FUNCTION; }
    virtual bool isEqual(const AbstractArithmetic *other) const;
    virtual std::string toString() const;

    std::string getIdentifier() const { return identifier; }
};

}

#endif //FUNCTION_H
