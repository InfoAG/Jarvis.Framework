#ifndef ABSTRACTSMARTLIST_H
#define ABSTRACTSMARTLIST_H

#include "AbstractList.h"
#include "AbstractListData.h"

namespace CAS {

/** Abstract base class for all lists with listwise COW
  * @author Alexander Schl�ter
  * @param T The type of objects to store
  * @param _ListData Type of list data for COW (e.g. RepetitiveLinkedListData for nodewise COW)
  * @param _BaseList Type of base list to inherit from (e.g. AbstractLinkedList for linked lists)
  */
template <class T, class _ListData, class _BaseList>
class AbstractSmartList : public _BaseList
{
protected:
    _ListData *listData; /**< A pointer to the list data */

    /** @brief Helper function for detaching from shared list data
      *
      * Call this to replace listData by a version you are allowed to change
      * without influencing other lists.
      */
    inline void detach() { listData = listData->detach(); };

public:
    inline AbstractSmartList() : listData(new _ListData) {}; /**< Constructor */
    /** Copy constructor
      * @param other Reference to the list to copy
      */
    inline AbstractSmartList(const AbstractSmartList &other) : listData(other.listData->copy()) {};
    virtual inline ~AbstractSmartList() { listData->release(); };

    virtual inline void append(const T &item) { detach(); listData->append(item); };
    virtual inline void prepend(const T &item){ detach(); listData->prepend(item); };
    virtual inline void insert(const T &item, unsigned int pos){ detach(); listData->insert(item, pos); };
    virtual inline void remove(unsigned int pos){ detach(); listData->remove(pos); };
    virtual inline void clear() { detach(); listData->clear(); };

    virtual inline const T &at(unsigned int pos) const { return listData->at(pos); };
    virtual inline bool isEmpty() const { return listData->isEmpty(); };
    virtual inline unsigned int size() const { return listData->size(); };

    AbstractSmartList &operator=(const AbstractSmartList &other) { listData->release(); listData = other.listData->copy(); return *this; };
};

}

#endif //ABSTRACTSMARTLIST_H
