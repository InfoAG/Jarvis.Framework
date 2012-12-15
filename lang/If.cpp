#include "If.h"

namespace CAS {

If::If(const If &other)
{
    for (const auto &conditional : other.conditionals)
        conditionals.emplace_back(conditional.first->copyEx(), conditional.second->copy());
}

AbstractExpression::ExpressionP If::execute(Scope &scope, const LoadFunc &load, const PrintFunc &print, ExecOption execOption) const
{
    std::vector<std::pair<AbstractExpression::ExpressionP, StatementP>> evalRes;
    auto it = conditionals.cbegin();
    for (; it != conditionals.cend(); ++it) {
        if (static_cast<BoolValue*>(it->first->executeExpression(scope, load, print, EAGER).get())->value())
            return it->second->execute(scope, load, print, execOption);
    }
    return make_unique<Void>();
        /*
        } else {
            evalRes.emplace_back(std::move(conditionResult), it->second->copy());
            ++it;
            break;
        }
    }

    if (it != conditionals.cend()) {
        for (; it != conditionals.cend(); ++it)
            evalRes.emplace_back(it->first->execute(scope, load, print, execOption), it->second->copy());
    }
    if (evalRes.empty()) return make_unique<Print>();
    else return make_unique<If>(std::move(evalRes));*/
}

TypeInfo If::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::VOID);
    for (const auto &cond : conditionals) {
        cond.first->typeCheck({{TypeInfo::BOOL}}, scope);
        cond.second->typeCheck(TypeCollection::all(), scope);
    }
    return TypeInfo::VOID;
}

std::string If::toString() const
{
    std::string result = "if ";
    for (auto it = conditionals.cbegin(); it != conditionals.cend(); ++it) {
        if (it != conditionals.cbegin()) result += " else if ";
        result += "(" + it->first->toString() + ") {\n" + it->second->toString() + "\n}";
    }
    return result;
}

bool If::equals(const AbstractStatement *other) const
{
    if (typeid(*other) != typeid(If) || static_cast<const If*>(other)->getConditionals().size() != conditionals.size()) return false;
    else {
        auto itOther = static_cast<const If*>(other)->getConditionals().cbegin();
        for (const auto &conditional : conditionals) {
            if (! (conditional.first->equals(itOther->first.get()) && conditional.second->equals(itOther->second.get()))) return false;
            ++itOther;
        }
        return true;
    }
}

}
