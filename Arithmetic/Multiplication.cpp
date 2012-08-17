#include "Multiplication.h"

namespace CAS {

std::unique_ptr<AbstractArithmetic> Multiplication::eval(const EvalInfo &ei) const
{
    std::vector<std::shared_ptr<AbstractArithmetic> > mergedOperands;
    for (const auto &operand : operands) {
        std::shared_ptr<AbstractArithmetic> evalRes = operand->eval(ei);
        if (evalRes->getType() == AbstractArithmetic::MULTIPLICATION) {
            std::vector<std::shared_ptr<AbstractArithmetic> > childOperands = static_cast<Multiplication*>(evalRes.get())->getOperands();
            mergedOperands.insert(begin(mergedOperands), begin(childOperands), end(childOperands));
        }
        else mergedOperands.push_back(evalRes);
    }
    int numberValue = 1;
    for (std::vector<std::shared_ptr<AbstractArithmetic> >::iterator it = begin(mergedOperands); it != end(mergedOperands);) {
        if ((*it)->getType() == AbstractArithmetic::NUMBERARITH) {
            numberValue *= static_cast<NumberArith*>(it->get())->getValue();
            it = mergedOperands.erase(it);
        } else ++it;
    }
    mergedOperands.push_back(std::make_shared<NumberArith>(numberValue));
    return std::unique_ptr<Multiplication>(new Multiplication(mergedOperands));
    /*
    std::unique_ptr<AbstractArithmetic> first_op_result = first_op->eval(ei), second_op_result = second_op->eval(ei);
    if (first_op_result->getType() == NUMBERARITH && second_op_result->getType() == NUMBERARITH)
        return std::unique_ptr<NumberArith>(new NumberArith(*(static_cast<NumberArith*>(first_op_result.release())) * *(static_cast<NumberArith*>(second_op_result.release()))));
    else
        return std::unique_ptr<AbstractArithmetic>(new Multiplication(std::move(first_op_result), std::move(second_op_result)));*/
}

std::string Multiplication::toString() const
{
    std::string result = operands.front()->toString();
    for (std::vector<std::shared_ptr<AbstractArithmetic> >::const_iterator it = ++(operands.begin()); it != operands.end(); ++it)
        result += "*" + (*it)->toString();
    return result;
}

bool Multiplication::isEqual(const AbstractArithmetic *other) const
{
    if (other->getType() != AbstractArithmetic::MULTIPLICATION) return false;
    return equalOperands(static_cast<const Multiplication*>(other)->getOperands(), operands);
}

}
