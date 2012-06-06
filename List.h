#ifndef LIST_H
#define LIST_H

#include "AbstractList.h"
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
class List : public AbstractList<T>
{
private:
    AbstractNode<T> *first; /**< Pointer to first node in list */
    AbstractNode<T> *last; /**< Pointer to last node in list */
    unsigned int _size; /**< List size */

protected:
    virtual inline AbstractNode<T> *getLast() const { return last; };

public:
    inline List() : first(0), last(0), _size(0) {}; /**< Constructor */
    /** Copy constructor
      * @param other The list to copy
      */
    List(const List &other);
    virtual inline ~List() {};

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

    bool operator==(const List &other) const;
    inline bool operator!=(const List &other) const { return ! (*this == other); };
    inline List operator+(const T &item) const { List result(*this); result.append(item); return result; };
    inline List operator+(const List &other) const { List result(*this); result += other; return result; };
    inline List &operator+=(const T &item) { append(item); };
    List &operator+=(const List &other);
    T &operator[](unsigned int pos) { iterator it(this->begin()); while (pos--) ++it; return *it; };
};

#include "List.cpp"

}

#endif //LIST_H
