#include "AbstractExpression.h"

namespace CAS {

std::string AbstractExpression::typeToString(ReturnType type)
{
    switch (type) {
    case NUMBER: return "number";
    case BOOL: return "bool";
    case LIST: return "list";
    }
}

}
