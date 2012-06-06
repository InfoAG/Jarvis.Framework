#ifndef ABSTRACTLIST_H
#define ABSTRACTLIST_H

#include "Container.h"
#include "AbstractNode.h"

namespace CAS {

/** Abstract base class providing the interface for all lists
  * @author Alexander Schlüter
  */
template <class T>
class AbstractList : Container
{
private:
    //! Abstract base class for list iterators
    class BaseIterator
    {
    private:
        const AbstractList *baseList; /**< Pointer to the list this iterator is based on */

    protected:
        AbstractNode<T> *target; /**< Pointer to targeted node */

    public:
        /** Constructor
          * @param target Pointer to target node
          * @param baseList Pointer to base list
          */
        inline BaseIterator(AbstractNode<T> *target = 0, const AbstractList  *baseList = 0) : target(target), baseList(baseList) {};
        /** Copy constructor
          * @param other Reference of the iterator to copy
          */
        inline BaseIterator(const BaseIterator &other) : target(other.target), baseList(other.baseList) {};
        //! Virtual destructor
        virtual inline ~BaseIterator() {};

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
    };

protected:
    /** @return A pointer to the last node in the list */
    virtual AbstractNode<T> *getLast() const = 0;

public:
    //! List iterator
    class iterator : public BaseIterator
    {
    public:
        /** Constructor
          * @param target Pointer to target node
          * @param baseList Pointer to base list
          */
        inline iterator(AbstractNode<T> *target = 0, const AbstractList *baseList = 0) : BaseIterator(target, baseList) {};
        /** Copy constructor
          * @param other Reference of the iterator to copy
          */
        inline iterator(const BaseIterator &other) : BaseIterator(other) {};

        inline T &operator*() const { return BaseIterator::target->getItem(); };
        inline T *operator->() const { return &BaseIterator::target->getItem(); };
    };

    //! Const list iterator
    class const_iterator : public BaseIterator
    {
    public:
        /** Constructor
          * @param target Pointer to target node
          * @param baseList Pointer to base list
          */
        inline const_iterator(AbstractNode<T> *target = 0, const AbstractList *baseList = 0) : BaseIterator(target, baseList) {};
        /** Copy constructor
          * @param other Reference of the iterator to copy
          */
        inline const_iterator(const BaseIterator &other) : BaseIterator(other) {};

        inline const T &operator*() const { return BaseIterator::target->getItem(); };
        inline const T *operator->() const { return &BaseIterator::target->getItem(); };

    };

    //! Default constructor
    inline AbstractList() {}; //to prevent bug from MSVC
    //! Virtual destructor
    virtual inline ~AbstractList() {};

    /** Append one item to list
      * @param item The item to append
      */
    virtual void append(const T &item) = 0;
    /** Prepend one item to list
      * @param item The item to prepend
      */
    virtual void prepend(const T &item) = 0;
    /** Insert one item into list
      * @param item The item to insert
      * @param pos The position for the new item
      */
    virtual void insert(const T &item, unsigned int pos) = 0;
    /** Remove one item from list
      * @param pos Position of the item to remove
      */
    virtual void remove(unsigned int pos) = 0;
    /** Delete all list items */
    virtual void clear() = 0;

    /** @return Returns an iterator to the first item of the list */
    virtual iterator begin() = 0;
    /** @return Returns a const_iterator to the first item of the list */
    virtual const_iterator begin() const = 0;
    /** @return Returns an iterator pointing after the last item in the list */
    virtual iterator end() = 0;
    /** @return Returns a const_iterator pointing after the last item in the list */
    virtual const_iterator end() const = 0;
    /** Access one element based on its position
      * @param pos The position to access
      * @return A reference to the item
      */
    virtual const T &at(unsigned int pos) const = 0;
    /** @return Returns true if the list is empty */
    virtual bool isEmpty() const = 0;
    /** @return The list's size */
    virtual unsigned int size() const = 0;
};

#include "AbstractList.cpp"

}

#endif //ABSTRACTLIST_H
