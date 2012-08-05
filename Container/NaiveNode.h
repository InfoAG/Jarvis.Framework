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
    inline NaiveNode(const T &item, AbstractNode<T> *previous = nullptr, AbstractNode<T> *next = nullptr) : AbstractNode<T>(previous, next), item(item) {};
    inline NaiveNode(T &&item, AbstractNode<T> *previous = nullptr, AbstractNode<T> *next = nullptr) : AbstractNode<T>(previous, next), item(std::forward<T>(item)) {};
    /** Copy constructor
      * @param other A reference to the SmartNode to copy
      * @param previous A pointer to the previous node in list
      * @param next A pointer to the next node in list
      */
    inline NaiveNode(const NaiveNode &other, AbstractNode<T> *previous = nullptr, AbstractNode<T> *next = nullptr) : AbstractNode<T>(previous, next), item(other.item) {};
    inline NaiveNode *copy(AbstractNode<T> *previous = nullptr, AbstractNode<T> *next = nullptr) const { return new NaiveNode(*this, previous, next); };

    virtual inline T &getItem() { return item; };
    virtual inline NaiveNode *getPrevious() const { return static_cast<NaiveNode*>(AbstractNode<T>::previous); };
    virtual inline NaiveNode *getNext() const { return static_cast<NaiveNode*>(AbstractNode<T>::next); };
};

}

#endif //NAIVENODE_H
