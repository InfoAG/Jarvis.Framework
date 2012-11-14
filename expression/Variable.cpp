#include "Variable.h"

namespace CAS {

AbstractExpression::EvalRes Variable::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    if (scope.hasVar(identifier)) {
        auto varDef = scope.getVar(identifier);
        if (varDef.second.recursion) throw "recursion";
        else if (lazy || varDef.second.definition == nullptr) {
            if (direct) throw "directnonono";
            else return std::make_pair(varDef.second.type, copy());
        } else if (direct && ! varDef.second.definition->isValue())
            throw "directnonono";
        else {
            Scope defScope(&varDef.first);
            VariableDefinition preventRecursion(varDef.second, true);
            defScope.declareVar(varDef.second.type, identifier);
            defScope.defineVar(identifier, std::move(preventRecursion));
            return std::make_pair(varDef.second.type, varDef.second.definition->eval(defScope, load, lazy, direct).second);
        }
    } else {
        scope.declareVar({TypeInfo::NUMBER}, identifier);
        return std::make_pair(TypeInfo{TypeInfo::NUMBER}, copy());
    }
}

bool Variable::equals(const AbstractExpression *other) const
{
    return typeid(*other) == typeid(Variable) && static_cast<const Variable*>(other)->getIdentifier() == identifier;
}

}
