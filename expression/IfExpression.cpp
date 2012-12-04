#include "IfExpression.h"

namespace CAS {

IfExpression::IfExpression(const IfExpression &other)
{
    for (const auto &conditional : other.conditionals)
        conditionals.emplace_back(conditional.first->copy(), conditional.second->copy());
}

AbstractExpression::ExpressionP IfExpression::execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption execOption) const
{
    std::vector<std::pair<ExpressionP, ExpressionP>> evalRes;
    auto it = conditionals.cbegin();
    for (; it != conditionals.cend(); ++it) {
        auto conditionResult = it->first->execute(scope, load, EAGER);
        if (typeid(*(conditionResult)) == typeid(BoolValue)) {
            if (static_cast<BoolValue*>(conditionResult.get())->value())
                return it->second->execute(scope, load, execOption);
        } else {
            evalRes.emplace_back(std::move(conditionResult), it->second->copy());
            ++it;
            break;
        }
    }

    if (it != conditionals.cend()) {
        for (; it != conditionals.cend(); ++it)
            evalRes.emplace_back(it->first->execute(scope, load, execOption), it->second->copy());
    }
    if (evalRes.empty()) return make_unique<OutputExpression>();
    else return make_unique<IfExpression>(std::move(evalRes));
}

TypeInfo IfExpression::typeCheck(const TypeCollection &candidates, Scope &scope)
{
    candidates.assertContains(*this, TypeInfo::VOID);
    for (const auto &cond : conditionals) {
        cond.first->typeCheck({{TypeInfo::BOOL}}, scope);
        cond.second->typeCheck(TypeCollection::all(), scope);
    }
    return TypeInfo::VOID;
}

std::string IfExpression::toString() const
{
    std::string result = "if ";
    for (auto it = conditionals.cbegin(); it != conditionals.cend(); ++it) {
        if (it != conditionals.cbegin()) result += " else if ";
        result += "(" + it->first->toString() + ") {\n" + it->second->toString() + "\n}";
    }
    return result;
}

bool IfExpression::equals(const AbstractExpression *other) const
{
    if (typeid(*other) != typeid(IfExpression) || static_cast<const IfExpression*>(other)->getConditionals().size() != conditionals.size()) return false;
    else {
        auto itOther = static_cast<const IfExpression*>(other)->getConditionals().cbegin();
        for (const auto &conditional : conditionals) {
            if (! (conditional.first->equals(itOther->first.get()) && conditional.second->equals(itOther->second.get()))) return false;
            ++itOther;
        }
        return true;
    }
}

}
