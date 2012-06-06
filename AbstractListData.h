#ifndef ABSTRACTLISTDATA_H
#define ABSTRACTLISTDATA_H

namespace CAS {

/** Abstract base class for all COW list data
  * @author Alexander Schlüter
  */
template <class T>
class AbstractListData
{
protected:
    unsigned int refcount; /**< Number of lists referencing this data */

public:
    inline AbstractListData() : refcount(1) {}; /**< Constructor */
    //! Virtual destructor
    virtual inline ~AbstractListData() {};

    /** Handles copying by increasing intern reference count
      * @return A pointer to this data object
      */
    virtual inline AbstractListData *copy() = 0;
    /** @brief Handles changing of list data in a COW environment
      *
      * Call this to get a pointer to list data you are allowed to change
      * without influencing other lists.
      * @return A pointer to a detached verson of this list data
      */
    virtual AbstractListData *detach() = 0;
    //! Removes a reference and deletes when appropriate
    inline void release() { if (--refcount < 1) delete this; }; //needs virtual destructor to prevent slicing
};

}

#endif //ABSTRACTLISTDATA_H
