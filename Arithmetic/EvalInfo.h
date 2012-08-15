#ifndef EVALINFO_H
#define EVALINFO_H

#include <map>
#include <string>
#include <memory>

namespace CAS {

class AbstractArithmetic;

struct EvalInfo
{
    typedef std::map<std::string, std::unique_ptr<AbstractArithmetic> > Definitions;
    Definitions variables;
    Definitions functions;
};

}

#endif //EVALINFO_H
