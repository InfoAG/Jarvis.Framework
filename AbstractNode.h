#ifndef ABSTRACTNODE_H
#define ABSTRACTNODE_H

//! A list node.
template <class T>
struct AbstractNode
{
    AbstractNode *previous; /**< Pointer to previous node in list. */
    AbstractNode *next; /**< Pointer to next node in list. */

    /** Copy constructor.
      * @param other Node to copy.
      * @param previous Pointer to previous node.
      * @param next Pointer to next node.
      */
    //inline Node(const Node &other, Node *previous = 0, Node *next = 0) : data(other.data->copy()), previous(previous), next(next) {};
    /** Copy constructor.
      * @param item Item to store.
      * @param previous Pointer to previous node.
      * @param next Pointer to next node.
      */
    inline AbstractNode(AbstractNode *previous = 0, AbstractNode *next = 0) : previous(previous), next(next) {};
    virtual AbstractNode *copy(AbstractNode *previous = 0, AbstractNode *next = 0) const = 0;
    /** Destructor.
      * @see release()
      */
    //inline ~AbstractNode() { data->release(); };

    /**
      * @return Returns a reference to the item.
      */
    virtual T &getItem() = 0;
};

#include "AbstractNode.cpp"

#endif //ABSTRACTNODE_H
