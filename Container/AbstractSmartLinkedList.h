#ifndef ABSTRACTSMARTLINKEDLIST_H
#define ABSTRACTSMARTLINKEDLIST_H

#include "AbstractSmartList.h"

namespace CAS {

template <class T, class _ListData>
class AbstractSmartLinkedList : public AbstractSmartList<T, _ListData>
{
public:
    virtual inline iterator begin() { detach(); return iterator(listData->getFirst(), this); };
    virtual inline const_iterator begin() const { return const_iterator(listData->getFirst(), this); };
    virtual inline iterator end() { detach(); return iterator(listData->getLast(), this); };
    virtual inline const_iterator end() const { return const_iterator(listData->getLast(), this); };

    inline bool operator==(const AbstractSmartLinkedList &other) const { return *listData == other.listData; };
    inline bool operator!=(const AbstractSmartLinkedList &other) const { return ! (*this == other); };
    inline AbstractSmartLinkedList operator+(const T &item) const { AbstractSmartLinkedList result(*this); result.append(item); return result; };
    inline AbstractSmartLinkedList operator+(const AbstractSmartLinkedList &other) const { AbstractSmartLinkedList result(*this); result += other; return result; };
    inline AbstractSmartLinkedList &operator+=(const T &item) { append(item); };
    inline AbstractSmartLinkedList &operator+=(const AbstractSmartLinkedList &other) { detach(); *listData += *(other.listData); return *this; };
    inline T &operator[](unsigned int pos) { iterator it(this->begin()); while (pos--) ++it; return *it; };
};

}
#endif //ABSTRACTSMARTLINKEDLIST_H
