#ifndef ABSTRACTEXPRESSION_H
#define ABSTRACTEXPRESSION_H

#include "Scope.h"
#include "global.h"
#include <string>
#include <vector>

namespace CAS {

//! Abstract base class for all expression objects
class AbstractExpression
{   
public:
    typedef std::vector<std::unique_ptr<AbstractExpression>> Operands;

    virtual ~AbstractExpression() {} //!< Virtual destructor to prevent slicing
    /**
     * Virtual copy constructor
     * @return AbstractExpression* pointing to a copy of this object
     */
    virtual std::unique_ptr<AbstractExpression> copy() const = 0;

    /**
     * Evaluate the arithmetical tree beginning at this object as root node and using the definitions in ei
     * @param ei EvalInfo object containing definitions
     * @return AbstractExpression* pointing to the root of an arithmetical tree representing the result
     */
    virtual std::unique_ptr<AbstractExpression> eval(Scope &scope, bool lazy = false) const = 0;
    virtual std::string toString() const = 0; //!< @return String representation of the arithmetical tree starting at this node
    virtual bool equals(const AbstractExpression *other) const = 0;
};

}

#endif //ABSTRACTEXPRESSION_H
