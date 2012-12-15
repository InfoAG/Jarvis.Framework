#include "FunctionSignature.h"

namespace CAS {

std::string FunctionSignature::toString() const
{
    std::string result = id + "(";
    if (! argumentTypes.empty()) {
        for (auto it = argumentTypes.cbegin(); it != argumentTypes.cend() - 1; it++)
            result += it->toString() + ", ";
        result += argumentTypes.back().toString();
    }
    return result;
}

bool FunctionSignature::operator<(const FunctionSignature &other) const
{
    if (id == other.id) return argumentTypes < other.argumentTypes;
    else return id < other.id;
}

}
