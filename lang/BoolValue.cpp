#include "BoolValue.h"

namespace CAS {

bool BoolValue::equals(const AbstractStatement *other) const
{
    return typeid(*other) == typeid(BoolValue) && static_cast<const BoolValue*>(other)->value() == value();
}

}
