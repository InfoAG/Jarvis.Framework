#ifndef EVALUATIONEXCEPTION_H
#define EVALUATIONEXCEPTION_H

#include "JarvisException.h"

namespace CAS {

class ExecutionException : public JarvisException
{
public:
    enum ExecEReason {
        FAILEDEAGER,
        RECURSION,
        NOCFUNCARGS,
        DIMMISMATCH
    };

private:
    std::string expr;
    ExecEReason _reason;

public:
    ExecutionException(std::string expr, ExecEReason reason = FAILEDEAGER) : expr(std::move(expr)), _reason(reason) {}
    ExecEReason reason() const { return _reason; }
    virtual std::string what() const;

    static ExecutionException failedEager(std::string expr) { return {std::move(expr), FAILEDEAGER}; }
    static ExecutionException recursion(std::string expr) { return {std::move(expr), RECURSION}; }
    static ExecutionException noCFuncArgs(std::string expr) { return {std::move(expr), NOCFUNCARGS}; }
    static ExecutionException dimMismatch(std::string expr) { return {std::move(expr), DIMMISMATCH}; }
};

}

#endif // EVALUATIONEXCEPTION_H
