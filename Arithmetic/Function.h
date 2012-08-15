#ifndef FUNCTION_H
#define FUNCTION_H

#include "AbstractArithmetic.h"
#include "../Container/SmartList.h"

namespace CAS {

class Function : public AbstractArithmetic
{
private:
    SmartList<AbstractArithmetic*> arguments;

public:
    Function(const SmartList<AbstractArithmetic*> arguments) : arguments(arguments) {}
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return std::unique_ptr<AbstractArithmetic>(new Function(*this)); }

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const;
    virtual ArithmeticType getType() const { return ADDITION; }
};

}

#endif //FUNCTION_H
