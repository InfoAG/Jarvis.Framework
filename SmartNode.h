#ifndef SMARTNODE_H
#define SMARTNODE_H

#include "AbstractNode.h"

template <class T>
struct SmartNode : AbstractNode<T>
{
    //! Smart node data for COW.
    class NodeData
    {
    private:
        T item; /**< Actual item data. */
        unsigned int refcount; /**< Number of nodes referencing this data. */

    public:
        /** Constructor.
          * @param item as the item to encapsulate.
          */
        inline NodeData(const T &item) : item(item), refcount(1) {};
        /** Adds a reference for a new node.
          * @return A pointer to this.
          * @see release()
          */
        inline NodeData *copy() { refcount++; return this; };
        /** Removes a reference and deletes when appropriate.
          * @see copy()
          */
        inline void release() { if (--refcount == 0) delete this; };
        inline NodeData *detach();

        inline T &getItem() { return item; };
    };

    NodeData *data; /**< Pointer to the NodeData object containing item data.*/

    inline SmartNode(const SmartNode &other, AbstractNode *previous = 0, AbstractNode *next = 0) : data(other.data->copy()), AbstractNode(previous, next) {};
    inline SmartNode(const T &item, AbstractNode *previous = 0, AbstractNode *next = 0) : data(new NodeData(item)), AbstractNode(previous, next) {};
    virtual inline SmartNode *copy(AbstractNode *previous = 0, AbstractNode *next = 0) const { return new SmartNode(*this, previous, next); };

    virtual inline T &getItem() { data = data->detach(); return data->getItem(); };
};

#include "SmartNode.cpp"

#endif //SMARTNODE_H
