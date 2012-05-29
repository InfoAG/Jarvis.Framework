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
        };

        NodeData *data; /**< Pointer to the NodeData object containing item data.*/
        Node *previous; /**< Pointer to previous node in list. */
        Node *next; /**< Pointer to next node in list. */

        /** Copy constructor.
          * @param other Node to copy.
          * @param previous Pointer to previous node.
          * @param next Pointer to next node.
          */
        inline Node(const Node &other, Node *previous = 0, Node *next = 0) : data(other.data->copy()), previous(previous), next(next) {};
        /** Copy constructor.
          * @param item Item to store.
          * @param previous Pointer to previous node.
          * @param next Pointer to next node.
          */
        inline Node(const T &item, Node *previous = 0, Node *next = 0) : data(new NodeData(item)), previous(previous), next(next) {};
        /** Destructor.
          * @see release()
          */
        inline ~Node() { data->release(); };

        /**
          * @return Returns a reference to the item.
          */
        inline T &getItem();
    };

    //! Abstract base class for list iterators.
    class BaseIterator
    {
    private:
        const List *baseList; /**< Pointer to the list this iterator is based on. */

    protected:
        Node *target; /**< Pointer to targeted node.*/

    public:
        /** Constructor.
          * @param target Pointer to target node.
          * @param baseList Pointer to base list.
          */
        inline BaseIterator(Node *target = 0, const List  *baseList = 0) : target(target), baseList(baseList) {};
        /** Copy constructor.
          * @param other Reference of the list to copy.
          */
        inline BaseIterator(const BaseIterator &other) : target(other.target), baseList(other.baseList) {};

        inline BaseIterator &operator++() { target = target->next; return *this; };
        inline BaseIterator operator++(int) { target = target->next; return BaseIterator(target->previous, baseList); };
        inline BaseIterator &operator--();
        inline BaseIterator operator--(int);
        inline bool operator==(const BaseIterator &other) const { return (target == other.target && baseList == other.baseList); };
        inline bool operator!=(const BaseIterator &other) const { return ! (*this == other); };
        inline BaseIterator operator+(int n) const;
        inline BaseIterator operator-(int n) const { return operator+(-n); };
        inline BaseIterator &operator+=(int n) { return *this = *this + n; };
        inline BaseIterator &operator-=(int n) { return *this = *this - n; };

        const Node * const getNode() const { return target; };
        const List * const getBaseList() const { return baseList; };
    };

    Node *first; /**< Pointer to first node in list.*/
    Node *last; /**< Pointer to last node in list.*/
    unsigned int _size; /**< List size.*/

public:
    //! List iterator.
    class iterator : public BaseIterator
    {
    public:
        inline iterator(Node *target = 0, const List *baseList = 0) : BaseIterator(target, baseList) {};
        inline iterator(const BaseIterator &other) : BaseIterator(other) {};

        inline T &operator*() { return target->getItem(); };
    };

    //! Const list iterator.
    class const_iterator : public BaseIterator
    {
    public:
        inline const_iterator(Node *target = 0, const List *baseList = 0) : BaseIterator(target, baseList) {};
        inline const_iterator(const BaseIterator &other) : BaseIterator(other) {};

        inline const T &operator*() { return target->getItem(); };

    };

    inline List() : first(0), last(0), _size(0) {};
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
    inline iterator begin() { return iterator(first, this); };
    /** @return Returns a const_iterator to the first item of the list.  */
    inline const_iterator begin() const { return const_iterator(first, this); };
    /** @return Returns an iterator pointing after the last item in the list.  */
    inline iterator end() { return iterator(0, this); };
    /** @return Returns a const_iterator pointing after the last item in the list.  */
    inline const_iterator end() const { return const_iterator(0, this); };
    /** Access one element based on its position.
      * @param pos The position to access.
      * @return A reference to the item.
      */
    const T &at(unsigned int pos) const;
    /** @return Returns true if the list is empty. */
    inline bool isEmpty() const { return size == 0; };
    /** @return The list's size.*/
    inline unsigned int size() const { return _size; };

    bool operator==(const List &other) const;
    inline bool operator!=(const List &other) const { return (! *this == other); };
    inline List operator+(const T &item) const { List result(*this); result.append(item); return result; };
    inline List operator+(const List &other) const { List result(*this); result += other; return result; };
    inline List &operator+=(const T &item) { append(item); return *this; }
    inline List &operator+=(const List &other);
    inline T &operator[](unsigned int pos) const;
};

#include "List.cpp"

#endif //LIST_H
