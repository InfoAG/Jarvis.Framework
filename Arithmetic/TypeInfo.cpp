#include "TypeInfo.h"

namespace CAS {

TypeInfo TypeInfo::fromString(const std::string &str)
{
    if (str == "number") return NUMBER;
    else if (str == "bool") return BOOL;
    else if (str.substr(0, 5) == "list<" && str.back() == '>') return {LIST, fromString(str.substr(5, str.length() - 6))};
    else throw "not a type";
}

std::string TypeInfo::toString() const
{
    switch (type) {
    case NUMBER: return "number";
    case BOOL: return "bool";
    case VOID: return "void";
    case LIST: return "list<" + next->toString() + ">";
    }
}

}
