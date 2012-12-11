#ifndef CONSTANT_H
#define CONSTANT_H

#include "AbstractExpression.h"
#include "NumberValue.h"

namespace CAS {

class Constant : public AbstractExpression
{
public:
    enum ConstantT {
        EULER,
        PI
    };

private:
    ConstantT _type;

public:
    Constant(ConstantT type) : _type(type) {}
    Constant(const Constant &other) : _type(other._type) {}
    virtual ExpressionP copy() const { return make_unique<Constant>(*this); }

    virtual ExpressionP execute(Scope &, const std::function<void(const std::string &)> &, ExecOption) const { return make_unique<NumberValue>(valueFromConstT(_type)); }
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &) { candidates.assertContains(*this, TypeInfo::NUMBER); return TypeInfo::NUMBER; }
    virtual ExpressionP differentiate(const std::string &) const { return make_unique<NumberValue>(0); }
    virtual std::string toString() const { return constTToString(_type); }
    virtual bool equals(const AbstractExpression *other) const;
    virtual bool isValue() const { return true; }

    ConstantT type() const { return _type; }

    static double valueFromConstT(ConstantT _type);
    static std::string constTToString(ConstantT _type);

    bool operator==(const Constant &other) const { return _type == other._type; }
};

}

#endif // CONSTANT_H
