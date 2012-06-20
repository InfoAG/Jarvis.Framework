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
    AbstractNode<T> *first; /**< Pointer to first node in list */
    AbstractNode<T> *last; /**< Pointer to last node in list */
    unsigned int _size; /**< List size */

protected:
    inline AbstractNode<T> *getFirst() const { return first; };
    inline AbstractNode<T> *getLast() const { return last; };

public:
    inline LinkedList() : first(0), last(0), _size(0) {}; /**< Constructor */
    /** Copy constructor
      * @param other The list to copy
      */
    LinkedList(const LinkedList &other);

    virtual void append(const T &item);
    virtual void prepend(const T &item);
    virtual void insert(const T &item, unsigned int pos);
    virtual void remove(unsigned int pos);
    virtual void clear();

    virtual inline iterator begin() { return iterator(first, this); };
    virtual inline const_iterator begin() const { return const_iterator(first, this); };
    virtual inline iterator end() { return iterator(0, this); };
    virtual inline const_iterator end() const { return const_iterator(0, this); };
    virtual const T &at(unsigned int pos) const;
    virtual inline bool isEmpty() const { return size() == 0; };
    virtual inline unsigned int size() const { return _size; };

    bool operator==(const LinkedList &other) const;
    inline bool operator!=(const LinkedList &other) const { return ! (*this == other); };
    inline LinkedList operator+(const T &item) const { LinkedList result(*this); result.append(item); return result; };
    inline LinkedList operator+(const LinkedList &other) const { LinkedList result(*this); result += other; return result; };
    inline LinkedList &operator+=(const T &item) { append(item); };
    LinkedList &operator+=(const LinkedList &other);
    T &operator[](unsigned int pos) { iterator it(this->begin()); while (pos--) ++it; return *it; };
};

#include "LinkedList.cpp"

}

#endif //LIST_H
