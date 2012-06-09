#ifndef ABSTRACTSMARTLIST_H
#define ABSTRACTSMARTLIST_H

#include "AbstractList.h"

namespace CAS {

/** Abstract base class for all lists with listwise COW
  * @author Alexander Schlüter
  */
template <class T, class _ListData>
class AbstractSmartList : public AbstractList<T>
{
protected:
    _ListData *listData; /**< A pointer to the list data */

    /** @brief Helper function for detaching from shared list data
      *
      * Call this to replace listData by a version you are allowed to change
      * without influencing other lists.
      */
    inline void detach() { listData = listData->detach(); };

/*protected:
    virtual inline AbstractNode<T> *getFirst() const { return listData->getFirst(); };
    virtual inline AbstractNode<T> *getLast() const { return listData->getLast(); };*/

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

    virtual inline iterator begin() = 0;
    virtual inline const_iterator begin() const = 0;
    virtual inline iterator end() = 0;
    virtual inline const_iterator end() const = 0;
    virtual inline const T &at(unsigned int pos) const { return listData->at(pos); };
    virtual inline bool isEmpty() const { return listData->isEmpty(); };
    virtual inline unsigned int size() const { return listData->size(); };

    /*
    inline bool operator==(const AbstractSmartList &other) const { return *listData == other.listData; };
    inline bool operator!=(const AbstractSmartList &other) const { return ! (*this == other); };
    inline AbstractSmartList operator+(const T &item) const { AbstractSmartList result(*this); result.append(item); return result; };
    inline AbstractSmartList operator+(const AbstractSmartList &other) const { AbstractSmartList result(*this); result += other; return result; };
    inline AbstractSmartList &operator+=(const T &item) { append(item); };
    inline AbstractSmartList &operator+=(const AbstractSmartList &other) { detach(); *listData += *(other.listData); return *this; };
    inline T &operator[](unsigned int pos) { iterator it(this->begin()); while (pos--) ++it; return *it; };
    */
};

}

#endif //ABSTRACTSMARTLIST_H
