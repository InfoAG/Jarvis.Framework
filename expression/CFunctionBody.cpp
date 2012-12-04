#include "CFunctionBody.h"

namespace CAS {

AbstractExpression::ExpressionP CFunctionBody::executeWithArgs(Operands args, Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const {
        auto result = evalFunc(args, scope, load, execOption);
        //Operands a = std::move(args);
        if (result == nullptr)
            return make_unique<Function>(identifier, std::move(args));
        else return result;
}

}
