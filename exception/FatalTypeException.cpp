#include "FatalTypeException.h"

namespace CAS {

std::string FatalTypeException::what() const
{
    if (_reason == MISMATCH)
        return "type mismatch: expression \"" + expr + "\" has unexpected type " + type + ".";
    else
        return "not a type: \"" + type + "\"";
}

}
