#ifndef ABSTRACTEXPRESSION_H
#define ABSTRACTEXPRESSION_H

#include "global.h"
#include <string>
#include <vector>
#include "TypeInfo.h"
#include "TypeCollection.h"

namespace CAS {

class Scope;

//! Abstract base class for all expression objects
class AbstractExpression
{   
public:
    typedef std::unique_ptr<AbstractExpression> ExpressionP;
    typedef std::vector<ExpressionP> Operands;

    enum ExecOption {
        STD,
        LAZY,
        EAGER
    };

    virtual ~AbstractExpression() {} //!< Virtual destructor to prevent slicing

    virtual ExpressionP copy() const = 0;
   // virtual ReturnType type() const = 0;
    /**
     * Evaluate the arithmetical tree beginning at this object as root node and using the definitions in ei
     * @param ei EvalInfo object containing definitions
     * @return AbstractExpression* pointing to the root of an arithmetical tree representing the result
     */
    virtual ExpressionP execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption = STD) const = 0;
    ExpressionP eval(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption = STD) { typeCheck(TypeCollection::all(), scope); return execute(scope, load, execOption); }
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope) = 0;
    virtual std::string toString() const = 0; //!< @return String representation of the arithmetical tree starting at this node
    virtual bool equals(const AbstractExpression *other) const = 0;
    virtual bool isValue() const { return false; }
};

}

#endif //ABSTRACTEXPRESSION_H
