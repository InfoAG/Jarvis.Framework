#ifndef SCOPEINFO_H
#define SCOPEINFO_H

#include <map>
#include <string>
#include <memory>
#include <vector>

namespace CAS {

class AbstractArithmetic;

struct ScopeInfo
{
    typedef std::map<std::string, std::shared_ptr<AbstractArithmetic>> VarDefs;
    typedef std::map<std::pair<std::string, unsigned int>, std::pair<std::vector<std::string>, std::shared_ptr<AbstractArithmetic>>> FuncDefs;
    VarDefs variables;
    FuncDefs functions;
};

}

#endif // SCOPEINFO_H
