#include "IfExpression.h"

namespace CAS {

IfExpression::IfExpression(const IfExpression &other)
{
    for (const auto &conditional : other.conditionals)
        conditionals.emplace_back(conditional.first->copy(), conditional.second->copy());
}

AbstractExpression::EvalRes IfExpression::eval(Scope &scope, const std::function<void(const std::string &)> &load, bool lazy, bool direct) const
{
    std::vector<std::pair<ExpressionP, ExpressionP>> evalRes;
    auto it = conditionals.cbegin();
    for (; it != conditionals.cend(); ++it) {
        auto conditionResult = it->first->eval(scope, load, lazy, true);
        if (conditionResult.first != TypeInfo::BOOL) throw "wrong argument";
        else if (typeid(*(conditionResult.second)) == typeid(BoolValue)) {
            if (static_cast<BoolValue*>(conditionResult.second.get())->value())
                return it->second->eval(scope, load, lazy, direct);
        } else {
            evalRes.emplace_back(std::move(conditionResult.second), it->second->copy());
            ++it;
            break;
        }
    }

    if (it != conditionals.cend()) {
        for (; it != conditionals.cend(); ++it) {
            auto conditionResult = it->first->eval(scope, load, lazy, direct);
            if (conditionResult.first != TypeInfo::BOOL) throw "wrong argument";
            evalRes.emplace_back(std::move(conditionResult.second), it->second->copy());
        }
    }
    if (evalRes.empty()) return std::make_pair(TypeInfo::VOID, make_unique<OutputExpression>());
    else return std::make_pair(TypeInfo::VOID, make_unique<IfExpression>(std::move(evalRes)));
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
