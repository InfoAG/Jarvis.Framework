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
protected:
    /** Abstract base class for list iterators
      * @param _BaseList Type of lists to iterate on
      */
    template <class _BaseList>
    class BaseIterator
    {
    protected:
        const _BaseList *baseList; /**< Pointer to the list this iterator is based on */

    public:
        /** Constructor
          * @param baseList Pointer to base list
          */
        BaseIterator(const _BaseList *baseList) : baseList(baseList) {};
        //! Virtual destructor
        virtual inline ~BaseIterator() {};

        inline bool operator==(const BaseIterator &other) const { return (baseList == other.baseList); };
    };

public:
    //! Abstract list iterator
    class iterator
    {
    public:
        virtual T &operator*() const = 0;
        virtual T *operator->() const = 0;
    };

    //! Abstract const list iterator
    class const_iterator
    {
    public:
        virtual const T &operator*() const = 0;
        virtual const T *operator->() const = 0;
    };

    //! Virtual destructor
    virtual inline ~AbstractList() {};

    /** Remove one item from list
      * @param pos Position of the item to remove
      */
    virtual void remove(unsigned int pos) = 0;
    /** Delete all list items */
    virtual void clear() = 0;
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

}

#endif //ABSTRACTLIST_H
