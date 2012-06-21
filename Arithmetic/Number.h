#ifndef NUMBER_H
#define NUMBER_H

#include "AbstractArithmetic.h"

namespace CAS {

class Number : public AbstractArithmetic
{
private:
    union {
        Integer integer;
        Rational rational;
    };
};

}

#endif NUMBER_H
