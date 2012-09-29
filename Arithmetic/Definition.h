#ifndef DEFINITION_H
#define DEFINITION_H

namespace CAS {

class AbstractExpression;

struct Definition
{
    std::shared_ptr<AbstractExpression> definition;
    bool evalFinished;

    Definition() {}
    Definition(std::shared_ptr<AbstractExpression> definition , bool evalFinished = false) : definition(std::move(definition)), evalFinished(evalFinished) {}
};

}

#endif // DEFINITION_H
