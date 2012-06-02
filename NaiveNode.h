#ifndef NAIVENODE_H
#define NAIVENODE_H

#include "AbstractNode.h"

template <class T>
struct NaiveNode : public AbstractNode<T>
{
    T item;

    inline NaiveNode(const T &item, AbstractNode *previous = 0, AbstractNode *next = 0) : item(item), AbstractNode(previous, next) {};
    inline NaiveNode(const NaiveNode &other, AbstractNode *previous = 0, AbstractNode *next = 0) : item(other.item), AbstractNode(previous, next) {};
    virtual inline NaiveNode *copy(AbstractNode *previous = 0, AbstractNode *next = 0) const { return new NaiveNode(*this, previous, next); };

    virtual inline T &getItem() { return item; };
};

#endif //NAIVENODE_H
