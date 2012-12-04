#ifndef TYPEEXCEPTION_H
#define TYPEEXCEPTION_H

#include "JarvisException.h"

namespace CAS {

class UndecidableTypeException : public JarvisException
{
private:
    std::string expr;

public:
    UndecidableTypeException(std::string expr) : expr(std::move(expr)) {}
    virtual std::string what() const { return "type of expression \"" + expr + "\" cannot be resolved."; }
};

}

#endif // TYPEEXCEPTION_H
