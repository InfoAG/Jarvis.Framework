#ifndef ABSTRACTLINKEDLIST_H
#define ABSTRACTLINKEDLIST_H

#include "AbstractList.h"

namespace CAS {

/** Abstract base class providing the interface for all linked lists (mostly iterators)
  * @author Alexander Schlüter
  */
template <class T>
class AbstractLinkedList : public AbstractList<T>
{
private:
    //! Abstract base class for linked list iterators
    class BaseIterator : public AbstractList<T>::template BaseIterator<AbstractLinkedList>
    {
    protected:
        AbstractNode<T> *target; /**< Pointer to targeted node */

    public:
        /** Constructor
          * @param target Pointer to target node
          * @param baseList Pointer to base list
          */
        inline BaseIterator(AbstractNode<T> *target = 0, const AbstractLinkedList<T> *baseList = 0) : AbstractList<T>::template BaseIterator<AbstractLinkedList>(baseList), target(target) {};
        /** Copy constructor
          * @param other Reference of the iterator to copy
          */
        inline BaseIterator(const BaseIterator &other) : AbstractList<T>::template BaseIterator<AbstractLinkedList>(other), target(other.target) {};

        inline BaseIterator &operator++() { target = target->next; return *this; };
        inline BaseIterator operator++(int) { BaseIterator result(*this); target = target->next; return result; };
        inline BaseIterator &operator--();
        inline BaseIterator &operator--(int);
        inline bool operator==(const BaseIterator &other) const { return (target == other.target && AbstractList<T>::template BaseIterator<AbstractLinkedList>::operator==(other)); };
        inline bool operator!=(const BaseIterator &other) const { return ! (*this == other); };
        inline BaseIterator operator+(int n) const;
        inline BaseIterator operator-(int n) const { return operator+(-n); };
        inline BaseIterator &operator+=(int n) { return *this = *this + n; };
        inline BaseIterator &operator-=(int n) { return *this = *this - n; };
    };

protected:
    virtual AbstractNode<T> *getFirst() const = 0; /**< @return Pointer to the list's first node */
    virtual AbstractNode<T> *getLast() const = 0; /**< @return Pointer to the list's last node */

public:
    //! Linked list iterator
    class iterator : public AbstractList<T>::iterator, public BaseIterator
    {
    private:
        /** Copy constructor
          * Needed to inherit BaseIterator's operators, but kept private and explicit to prevent
          * illegal conversion from const_iterator to iterator, which would allow non-const access to a
          * const list.
          * @param other Reference to the BaseIterator to copy
          */
        explicit inline iterator(const BaseIterator &other) : BaseIterator(other) {};

    public:
        /** Constructor
          * @param target Pointer to target node
          * @param baseList Pointer to base list
          */
        inline iterator(AbstractNode<T> *target = 0, const AbstractLinkedList *baseList = 0) : BaseIterator(target, baseList) {};
        /** Copy constructor
          * @param other Reference of the iterator to copy
          */
        inline iterator(const iterator &other) : BaseIterator(other) {};

        inline T &operator*() const { return BaseIterator::target->getItem(); };
        inline T *operator->() const { return &BaseIterator::target->getItem(); };
        inline iterator &operator++() { BaseIterator::operator++(); return *this; };
        inline iterator operator++(int) { return iterator(BaseIterator::operator++(int())); };
        inline iterator &operator--() { BaseIterator::operator--(); return *this;  };
        inline iterator operator--(int) { return iterator(BaseIterator::operator--(0)); };
        inline iterator operator+(int n) const { return iterator(BaseIterator::operator+(n)); };
        inline iterator operator-(int n) const { return iterator(BaseIterator::operator-(n)); };
        inline iterator &operator+=(int n) { BaseIterator::operator+=(n); return *this; };
        inline iterator &operator-=(int n) { BaseIterator::operator-=(n); return *this; };
    };

    //! Const linked list iterator
    class const_iterator : public AbstractList<T>::const_iterator, public BaseIterator
    {
    public:
        /** Constructor
          * @param target Pointer to target node
          * @param baseList Pointer to base list
          */
        inline const_iterator(AbstractNode<T> *target = 0, const AbstractLinkedList *baseList = 0) : BaseIterator(target, baseList) {};
        /** Copy constructor
          * @param other Reference of the iterator to copy
          */
        inline const_iterator(const BaseIterator &other) : BaseIterator(other) {};

        inline const T &operator*() const { return BaseIterator::target->getItem(); };
        inline const T *operator->() const { return &BaseIterator::target->getItem(); };
        inline const_iterator &operator++() { BaseIterator::operator++(); return *this; };
        inline const_iterator operator++(int) { return BaseIterator::operator++(int()); };
        inline const_iterator &operator--() { BaseIterator::operator--(); return *this; };
        inline const_iterator operator--(int) { return BaseIterator::operator--(0); };
        inline const_iterator operator+(int n) const { return BaseIterator::operator+(n); };
        inline const_iterator operator-(int n) const { return BaseIterator::operator-(n); };
        inline const_iterator &operator+=(int n) { BaseIterator::operator+=(n); return *this; };
        inline const_iterator &operator-=(int n) { BaseIterator::operator-=(n); return *this; };
    };

    /** @return Returns an iterator to the first item of the list */
    virtual iterator begin() = 0;
    /** @return Returns a const_iterator to the first item of the list */
    virtual const_iterator begin() const = 0;
    /** @return Returns an iterator pointing after the last item in the list */
    virtual iterator end() = 0;
    /** @return Returns a const_iterator pointing after the last item in the list */
    virtual const_iterator end() const = 0;
};

#include "AbstractLinkedList.cpp"

}

#endif //ABSTRACTLINKEDLIST_H
