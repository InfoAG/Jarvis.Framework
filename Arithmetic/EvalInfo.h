#ifndef EVALINFO_H
#define EVALINFO_H

#include <map>
#include <string>
#include <memory>
#include <vector>

namespace CAS {

class AbstractArithmetic;

struct EvalInfo
{
    typedef std::map<std::pair<std::string, unsigned int>, std::pair<std::vector<std::string>, std::shared_ptr<AbstractArithmetic>>> FuncDefs;
    std::map<std::string, std::shared_ptr<AbstractArithmetic>> variables;
    FuncDefs functions;
};

}

#endif //EVALINFO_H
