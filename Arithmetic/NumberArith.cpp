#include "NumberArith.h"

namespace CAS {

std::string NumberArith::getString() const
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

}
