#include "NumberArith.h"

namespace CAS {

std::string NumberArith::toString() const
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

}
