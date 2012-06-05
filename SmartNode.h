#ifndef SMARTNODE_H
#define SMARTNODE_H

#include "AbstractNode.h"

/** COW-enabled list node for a doubly linked list
  * @author Alexander Schlüter
  */
template <class T>
struct SmartNode : AbstractNode<T>
{
    //! Smart node data for COW.
    class NodeData
    {
    private:
        T item; /**< Actual item data */
        unsigned int refcount; /**< Number of nodes referencing this data */

    public:
        /** Constructor
          * @param item The item to encapsulate
          */
        inline NodeData(const T &item) : item(item), refcount(1) {};
        /** Adds a reference for a new node
          * @return A pointer to this
          * @see release()
          */
        inline NodeData *copy() { refcount++; return this; };
        /** Removes a reference and deletes when appropriate
          * @see copy()
          */
        inline void release() { if (--refcount == 0) delete this; };
        /** Handles changing of items in a COW environment
          * @return A pointer to version of this node data you are allowed to change
          */
        inline NodeData *detach();

        inline T &getItem() { return item; }; /**< @return A reference to the item */
    };

    NodeData *data; /**< Pointer to the NodeData object containing item data */

    /** Constructor
      * @param item The item to store in this node
      * @param previous A pointer to the previous node in list
      * @param next A pointer to the next node in list
      */
    inline SmartNode(const T &item, AbstractNode *previous = 0, AbstractNode *next = 0) : data(new NodeData(item)), AbstractNode(previous, next) {};
    /** Copy constructor
      * @param other A reference to the SmartNode to copy
      * @param previous A pointer to the previous node in list
      * @param next A pointer to the next node in list
      */
    inline SmartNode(const SmartNode &other, AbstractNode *previous = 0, AbstractNode *next = 0) : data(other.data->copy()), AbstractNode(previous, next) {};
    virtual inline ~SmartNode() { data->release(); };

    virtual inline SmartNode *copy(AbstractNode *previous = 0, AbstractNode *next = 0) const { return new SmartNode(*this, previous, next); };

    virtual inline T &getItem() { data = data->detach(); return data->getItem(); };
};

#include "SmartNode.cpp"

#endif //SMARTNODE_H
