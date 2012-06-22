#ifndef VARIABLE_H
#define VARIABLE_H

#include "AbstractArithmetic.h"
#include <string>

namespace CAS {

class Variable : public AbstractArithmetic
{
private:
    std::string identifier;

public:
    inline Variable(const std::string &identifier) : identifier(identifier) {};
    virtual std::unique_ptr<AbstractArithmetic> copy() const { return std::unique_ptr<AbstractArithmetic>(new Variable(*this)); };

    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const { return copy(); };
    virtual ArithmeticType getType() const { return VARIABLE; };
};

}

#endif //VARIABLE_H
