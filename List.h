#ifndef LIST_H
#define LIST_H

#include "Container.h"

/** @brief List class implemented as doubly linked list with nodewise COW.
  *
  * Optimized for copying of lists with large elements, insert / remove.
  * Suboptimal for small elements and random access.
  *
  * @author Alexander Schlüter
  */

template <class T>
class List : Container
{
private:
    //! A list node.
    struct Node
    {
        //! Smart node data for COW.
        struct NodeData
        {
            T item; /**< Actual item data. */
            unsigned int refcount; /**< Number of nodes referencing this data. */

            /** Constructor.
              * @param item as the item to encapsulate.
              */
            NodeData(const T &item) : item(item), refcount(1) {};
            /** Adds a reference for a new node.
              * @return A pointer to this.
              * @see release()
              */
            NodeData *copy() { refcount++; return this; };
            /** Removes a reference and deletes when appropriate.
              * @see copy()
              */
            void release() { if (--refcount == 0) delete this; };
        };

        NodeData *data; /**< Pointer to the NodeData object containing item data.*/
        Node *previous; /**< Pointer to previous node in list. */
        Node *next; /**< Pointer to next node in list. */

        /** Copy constructor.
          * @param other Node to copy.
          * @param previous Pointer to previous node.
          * @param next Pointer to next node.
          */
        Node(const Node &other, Node *previous = 0, Node *next = 0) : data(other.data->copy()), previous(previous), next(next) {};
        /** Copy constructor.
          * @param item Item to store.
          * @param previous Pointer to previous node.
          * @param next Pointer to next node.
          */
        Node(const T &item, Node *previous = 0, Node *next = 0) : data(new NodeData(item)), previous(previous), next(next) {};
        /** Destructor.
          * @see release()
          */
        ~Node() { data->release(); };

        /**
          * @return Returns a reference to the item.
          */
        inline T &getItem();
    };

    Node *first; /**< Pointer to first node in list.*/
    Node *last; /**< Pointer to last node in list.*/
    unsigned int size; /**< List size.*/

public:
    class iterator
    {
    private:
        Node *target; /**< Pointer to targeted node.*/

    public:
        /** Constructor.
          * @param target Pointer to target node.
          */
        iterator(Node *target = 0) : target(target) {};

        T &operator*() const { return target->getItem(); };
        iterator &operator++() { target = target->next; return *this; };
        iterator &operator++(int) { target = target->next; return iterator(target->previous); };
        bool operator==(const iterator &other) const { return target == other.target; };
        bool operator!=(const iterator &other) const { return target != other.target; };
    };

    List() : first(0), last(0), size(0) {};
    List(const List<T> &other);

    /** Append one item to list.
      * @param item The item to append.
      */
    void append(const T &item);
    /** Prepend one item to list.
      * @param item The item to prepend.
      */
    void prepend(const T &item);
    /** Insert one item into list.
      * @param item The item to insert.
      * @param pos The position for the new item.
      */
    void insert(const T &item, unsigned int pos);
    /** Remove one item from list.
      * @param pos Position of the item to remove.
      */
    void remove(unsigned int pos);
    /** Delete all list items. */
    void clear();

    /** @return Returns an iterator to the first item of the list.  */
    iterator begin() const { return iterator(first); };
    /** @warning broken @return Returns an iterator that sucks.  */
    iterator end() const { return iterator(); };
    /** Access one element based on its position.
      * @param pos The position to access.
      * @return A reference to the item.
      */
    const T &at(unsigned int pos) const;
    /** @return The list's size.*/
    inline unsigned int getSize() const { return this->size; };
};

#include "List.cpp"

#endif //LIST_H
