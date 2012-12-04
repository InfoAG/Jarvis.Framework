#ifndef IMPORTEXPRESSION_H
#define IMPORTEXPRESSION_H

#include "AbstractUnaryOperation.h"
#include "OutputExpression.h"

namespace CAS {

class ImportExpression : public AbstractExpression
{
private:
    std::string fileName;

public:
    ImportExpression(std::string fileName) : fileName(std::move(fileName)) {}
    ImportExpression(const ImportExpression &other) : fileName(other.fileName) {}
    virtual ExpressionP copy() const { return make_unique<ImportExpression>(*this); }

    virtual ExpressionP execute(Scope &scope, const std::function<void(const std::string &)> &load, ExecOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &) { candidates.assertContains(*this, TypeInfo::VOID); return TypeInfo::VOID; }
    virtual bool equals(const AbstractExpression *other) const;
    virtual std::string toString() const { return "import " + fileName; }

    const std::string &getFileName() const { return fileName; }
};

}

#endif // IMPORTEXPRESSION_H
