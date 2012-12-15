#ifndef IMPORT_H
#define IMPORT_H

#include "AbstractUnaryExpression.h"
#include "Print.h"

namespace CAS {

class Import : public AbstractStatement
{
private:
    std::string fileName;

public:
    Import(std::string fileName) : fileName(std::move(fileName)) {}
    Import(const Import &other) : fileName(other.fileName) {}
    virtual StatementP copy() const { return make_unique<Import>(*this); }

    virtual AbstractExpression::ExpressionP execute(Scope &, const LoadFunc &load, const PrintFunc &, ExecOption) const;
    virtual TypeInfo typeCheck(const TypeCollection &candidates, Scope &) { candidates.assertContains(*this, TypeInfo::VOID); return TypeInfo::VOID; }
    virtual bool equals(const AbstractStatement *other) const;
    virtual std::string toString() const { return "import " + fileName; }

    const std::string &getFileName() const { return fileName; }
};

}

#endif // IMPORT_H
