#ifndef ABSTRACTSTATEMENT_H
#define ABSTRACTSTATEMENT_H

#include "global.h"
#include <string>
#include <vector>
#include "TypeInfo.h"
#include "TypeCollection.h"
#include "exception/InvalidTreeException.h"

namespace CAS {

class Scope;
class AbstractExpression;

//! Abstract base class for all expression objects
class AbstractStatement
{   
public:
    typedef std::unique_ptr<AbstractStatement> StatementP;
    typedef std::vector<StatementP> Statements;
    typedef std::function<void(const std::string &)> LoadFunc;
    typedef std::function<void(const std::string &)> PrintFunc;

    enum ExecOption {
        STD,
        LAZY,
        EAGER
    };

    virtual ~AbstractStatement() {} //!< Virtual destructor to prevent slicing

    virtual StatementP copy() const = 0;
   // virtual ReturnType type() const = 0;
    /**
     * Evaluate the arithmetical tree beginning at this object as root node and using the definitions in ei
     * @param ei EvalInfo object containing definitions
     * @return AbstractStatement* pointing to the root of an arithmetical tree representing the result
     */
    virtual std::unique_ptr<AbstractExpression> execute(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption = STD) const = 0;
    std::unique_ptr<AbstractExpression> eval(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption = STD);
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &scope) = 0;

    virtual std::string toString() const = 0; //!< @return String representation of the arithmetical tree starting at this node
    virtual bool equals(const AbstractStatement *other) const = 0;
};

}

#endif //ABSTRACTSTATEMENT_H
