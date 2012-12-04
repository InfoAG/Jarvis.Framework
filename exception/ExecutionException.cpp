#include "ExecutionException.h"

namespace CAS {

std::string ExecutionException::what() const
{
    switch (_reason) {
    case FAILEDEAGER:
        return "\"" + expr + "\" is not defined.";
    case RECURSION:
        return "recursive definition for \"" + expr + "\"";
    case NOCFUNCARGS:
        return "function " + expr + " has to be called with arguments.";
    case DIMMISMATCH:
        return expr;
    }
}

}
