#ifndef INVALIDTREEEXCEPTION_H
#define INVALIDTREEEXCEPTION_H

#include "JarvisException.h"

namespace CAS {

class InvalidTreeException : public JarvisException
{
private:
    std::string expr, msg;

public:
    InvalidTreeException(std::string expr, std::string msg) : expr(std::move(expr)), msg(std::move(msg)) {}
    virtual std::string what() const { return "Invalid expression tree: " + msg; }
};

}

#endif // INVALIDTREEEXCEPTION_H
