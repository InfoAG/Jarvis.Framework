#include "CFunctionBody.h"

namespace CAS {

AbstractExpression::ExpressionP CFunctionBody::evalWithArgs(Operands args, Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const {
        auto result = evalFunc(args, scope, load, lazy, direct);
        //Operands a = std::move(args);
        if (result == nullptr)
            return make_unique<Function>(identifier, std::move(args));
        else return result;
}

}
