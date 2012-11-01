#ifndef ABSTRACTEXPRESSION_H
#define ABSTRACTEXPRESSION_H

#include "global.h"
#include <string>
#include <vector>

namespace CAS {

class Scope;

//! Abstract base class for all expression objects
class AbstractExpression
{   
public:
    typedef std::unique_ptr<AbstractExpression> ExpressionP;
    typedef std::vector<ExpressionP> Operands;

    enum ReturnType {
        NUMBER,
        LIST,
        BOOL,
        UNKNOWN
    };

    typedef std::pair<ReturnType, ExpressionP> EvalRes;

    virtual ~AbstractExpression() {} //!< Virtual destructor to prevent slicing

    virtual ExpressionP copy() const = 0;
   // virtual ReturnType type() const = 0;
    /**
     * Evaluate the arithmetical tree beginning at this object as root node and using the definitions in ei
     * @param ei EvalInfo object containing definitions
     * @return AbstractExpression* pointing to the root of an arithmetical tree representing the result
     */
    virtual EvalRes eval(Scope &scope, bool lazy = false) const = 0;
    virtual std::string toString() const = 0; //!< @return String representation of the arithmetical tree starting at this node
    virtual bool equals(const AbstractExpression *other) const = 0;

    static std::string typeToString(ReturnType type);
};

}

#endif //ABSTRACTEXPRESSION_H
