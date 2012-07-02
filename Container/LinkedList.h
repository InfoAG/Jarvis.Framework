#ifndef LIST_H
#define LIST_H

#include "AbstractLinkedList.h"
#include "NaiveNode.h"

namespace CAS {

/** @brief Doubly linked list
  *
  * Simple doubly linked list without listwise COW.
  * @param T The type of objects to store
  * @param _Node The type of nodes used internally
  * @author Alexander Schlüter
  */
template <class T, class _Node = NaiveNode<T> >
class LinkedList : public AbstractLinkedList<T>
{
private:
    _Node *first; /**< Pointer to first node in list */
    _Node *last; /**< Pointer to last node in list */
    unsigned int _size; /**< List size */

protected:
    inline AbstractNode<T> *getFirst() const { return first; };
    inline AbstractNode<T> *getLast() const { return last; };

public:
    inline LinkedList() : first(nullptr), last(nullptr), _size(0) {}; /**< Constructor */
    /** Copy constructor
      * @param other The list to copy
      */
    LinkedList(const LinkedList &other);
    /** Move constructor
      * @param other The list to move
      */
    LinkedList(LinkedList &&other) : first(other.first), last(other.last), _size(other.size()) {};

    /** Append one item to list
      * @param item The item to append
      */
    void append(const T &item);
    /**
     * @overload
     */
    void append(T &&item);
    /** Prepend one item to list
      * @param item The item to prepend
      */
    void prepend(const T &item);
    /**
     * @overload
     */
    void prepend(T &&item);
    /** Insert one item into list
      * @param item The item to insert
      * @param pos The position for the new item
      */
    void insert(const T &item, unsigned int pos);
    /**
     * @overload
     */
    void insert(T &&item, unsigned int pos);
    virtual void remove(unsigned int pos);
    virtual void clear();

    virtual inline typename AbstractLinkedList<T>::iterator begin() { return typename AbstractLinkedList<T>::iterator(first, this); };
    virtual inline typename AbstractLinkedList<T>::const_iterator begin() const { return typename AbstractLinkedList<T>::const_iterator(first, this); };
    virtual inline typename AbstractLinkedList<T>::iterator end() { return typename AbstractLinkedList<T>::iterator(nullptr, this); };
    virtual inline typename AbstractLinkedList<T>::const_iterator end() const { return typename AbstractLinkedList<T>::const_iterator(nullptr, this); };
    virtual const T &at(unsigned int pos) const;
    virtual inline bool isEmpty() const { return size() == 0; };
    virtual inline unsigned int size() const { return _size; };

    bool operator==(const LinkedList &other) const;
    inline bool operator!=(const LinkedList &other) const { return ! (*this == other); };
    inline LinkedList operator+(const T &item) const { LinkedList result(*this); result.append(item); return result; };
    inline LinkedList operator+(const LinkedList &other) const { LinkedList result(*this); result += other; return result; };
    inline LinkedList &operator+=(const T &item) { append(item); };
    LinkedList &operator+=(const LinkedList &other);
    T &operator[](unsigned int pos) { typename AbstractLinkedList<T>::iterator it(this->begin()); while (pos--) ++it; return *it; };
};

#include "LinkedList.cpp"

}

#endif //LIST_H
