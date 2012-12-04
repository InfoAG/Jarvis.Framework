#ifndef JARVISEXCEPTION_H
#define JARVISEXCEPTION_H

#include <string>

namespace CAS {

class JarvisException
{
public:
    JarvisException() {}
    virtual std::string what() const = 0;
};

}

#endif // JARVISEXCEPTION_H
