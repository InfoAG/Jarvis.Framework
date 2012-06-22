#ifndef NAIVENODE_H
#define NAIVENODE_H

#include "AbstractNode.h"

namespace CAS {

template <class T>
struct NaiveNode : public AbstractNode<T>
{
    T item; /**< Actual item data */

    /** Constructor
      * @param item The item to store in this node
      * @param previous A pointer to the previous node in list
      * @param next A pointer to the next node in list
      */
    inline NaiveNode(const T &item, AbstractNode<T> *previous = 0, AbstractNode<T> *next = 0) : AbstractNode<T>(previous, next), item(item) {};
    /** Copy constructor
      * @param other A reference to the SmartNode to copy
      * @param previous A pointer to the previous node in list
      * @param next A pointer to the next node in list
      */
    inline NaiveNode(const NaiveNode &other, AbstractNode<T> *previous = 0, AbstractNode<T> *next = 0) : AbstractNode<T>(previous, next), item(other.item) {};
    virtual inline NaiveNode *copy(AbstractNode<T> *previous = 0, AbstractNode<T> *next = 0) const { return new NaiveNode(*this, previous, next); };

    virtual inline T &getItem() { return item; };
};

}

#endif //NAIVENODE_H
