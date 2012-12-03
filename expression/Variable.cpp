#include "Variable.h"

namespace CAS {

AbstractExpression::ExpressionP Variable::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    if (scope.hasVar(identifier)) {
        auto varDef = scope.getVar(identifier);
        if (varDef.second.recursion) throw "recursion";
        else if (lazy || varDef.second.definition == nullptr) {
            if (direct) throw "directnonono";
            else return copy();
        } else if (direct && ! varDef.second.definition->isValue())
            throw "directnonono";
        else {
            varDef.second.recursion = true;
            auto result = varDef.second.definition->eval(scope, load, lazy, direct);
            varDef.second.recursion = false;
            return result;
        }
    } else throw "not declared";
}

TypeInfo Variable::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    if (scope.hasVar(identifier)) {
        auto myT = scope.getVar(identifier).second.type;
        if (candidates.contains(myT)) return myT;
        else throw "typing";
    } else if (candidates.determinant()) {
        scope.declareVar(*(candidates.types.begin()), identifier);
        return *(candidates.types.begin());
    } else throw "typing";
}

bool Variable::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(Variable) && static_cast<const Variable*>(other)->getIdentifier() == identifier;
}

}
