#include "Constant.h"

namespace CAS {

bool Constant::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(Constant) && *this == *static_cast<const Constant*>(other);
}

double Constant::valueFromConstT(Constant::ConstantT type)
{
    switch (type) {
    case EULER: return 2.71828182845904524;
    case PI: return 3.14159265358979324;
    }
}

std::string Constant::constTToString(Constant::ConstantT type)
{
    switch (type) {
    case EULER: return "e";
    case PI: return "pi";
    }
}

}
