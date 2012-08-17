#ifndef ABSTRACTARITHMETIC_H
#define ABSTRACTARITHMETIC_H

#include "EvalInfo.h"
#include <memory>
#include <string>

namespace CAS {


//! Abstract base class for all arithmetical objects
class AbstractArithmetic
{
public:
    /**
     * Type info returned by getType() to identify arithmetical objects by AbstractArithmetic*
     * withouth using dynamic_cast
     */
    enum ArithmeticType {
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION,
        EXPONENTIATION,
        ROOT,
        LOGARITHM,
        SINUS,
        COSINUS,
        TANGENT,
        INTEGRAL,
        NUMBERARITH,
        VARIABLE,
        ASSIGNMENT
    };

    virtual ~AbstractArithmetic() {} //!< Virtual destructor to prevent slicing
    /**
     * Virtual copy constructor
     * @return AbstractArithmetic* pointing to a copy of this object
     */
    virtual std::unique_ptr<AbstractArithmetic> copy() const = 0;

    /**
     * Evaluate the arithmetical tree beginning at this object as root node and using the definitions in ei
     * @param ei EvalInfo object containing definitions
     * @return AbstractArithmetic* pointing to the root of an arithmetical tree representing the result
     */
    virtual std::unique_ptr<AbstractArithmetic> eval(const EvalInfo &ei) const = 0;
    virtual ArithmeticType getType() const = 0; //!< @return Type of the object
    virtual std::string toString() const = 0; //!< @return String representation of the arithmetical tree starting at this node
    virtual bool isEqual(const AbstractArithmetic *other) const = 0;
};

}

#endif //ABSTRACTARITHMETIC_H
