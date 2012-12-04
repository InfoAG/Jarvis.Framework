#ifndef EAGEREVALEXCEPTION_H
#define EAGEREVALEXCEPTION_H

#include "JarvisException.h"

namespace CAS {

class ScopeException : public JarvisException
{
public:
    enum Type {
        VAR,
        FUNC
    };

    enum ScopeEReason {
        MissingDeclaration,
        AlreadyDeclared
    };

private:
    std::string expr;
    Type type;
    ScopeEReason reason;

public:
    ScopeException(std::string expr, Type type, ScopeEReason reason) : expr(std::move(expr)), type(type), reason(reason) {}
    virtual std::string what() const;
};

}

#endif // EAGEREVALEXCEPTION_H
