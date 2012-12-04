#ifndef FATALTYPEEXCEPTION_H
#define FATALTYPEEXCEPTION_H

#include "JarvisException.h"

namespace CAS {

class FatalTypeException : public JarvisException
{
public:
    enum FatalTypeEReason {
        MISMATCH,
        INVALID
    };

private:
    std::string expr, type;
    FatalTypeEReason _reason;

public:
    FatalTypeException(std::string expr, std::string type, FatalTypeEReason reason) : expr(std::move(expr)), type(std::move(type)), _reason(reason) {}
    virtual std::string what() const;

    FatalTypeException inList() const { return {"[" + expr + "]", "list<" + type + ">", _reason}; }
    FatalTypeEReason reason() const { return _reason; }

    static FatalTypeException mismatch(std::string expr, std::string type) { return {std::move(expr), std::string(type), MISMATCH}; }
    static FatalTypeException invalid(std::string type) { return {std::string(), std::move(type), INVALID}; }
};

}

#endif // FATALTYPEEXCEPTION_H
