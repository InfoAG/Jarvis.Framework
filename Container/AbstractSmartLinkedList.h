#ifndef ABSTRACTSMARTLINKEDLIST_H
#define ABSTRACTSMARTLINKEDLIST_H

#include "AbstractSmartList.h"
#include "AbstractLinkedList.h"

namespace CAS {

/** Abstract base class for all linked lists with listwise COW
  * @param T The type of objects to store
  * @param _ListData Type of list data for COW (e.g. RepetitiveLinkedListData for nodewise COW)
  * @author Alexander Schlüter
  */
template <class T, class _ListData>
class AbstractSmartLinkedList : public AbstractSmartList<T, _ListData, AbstractLinkedList<T> >
{
protected:
    virtual AbstractNode<T> *getFirst() const { return listData->getFirst(); };
    virtual AbstractNode<T> *getLast() const { return listData->getLast(); };

public:
    inline typename AbstractLinkedList<T>::iterator begin() { detach(); return iterator(listData->getFirst(), this); };
    inline typename AbstractLinkedList<T>::const_iterator begin() const { return const_iterator(listData->getFirst(), this); };
    inline typename AbstractLinkedList<T>::iterator end() { detach(); return iterator(0, this); };
    inline typename AbstractLinkedList<T>::const_iterator end() const { return const_iterator(0, this); };

    inline bool operator==(const AbstractSmartLinkedList &other) const { return *listData == *(other.listData); };
    inline bool operator!=(const AbstractSmartLinkedList &other) const { return ! (*this == other); };
    inline AbstractSmartLinkedList operator+(const T &item) const { AbstractSmartLinkedList result(*this); result.append(item); return result; };
    inline AbstractSmartLinkedList operator+(const AbstractSmartLinkedList &other) const { AbstractSmartLinkedList result(*this); result += other; return result; };
    inline AbstractSmartLinkedList &operator+=(const T &item) { append(item); };
    inline AbstractSmartLinkedList &operator+=(const AbstractSmartLinkedList &other) { detach(); *listData += *(other.listData); return *this; };
    inline T &operator[](unsigned int pos) { iterator it(this->begin()); while (pos--) ++it; return *it; };
    using AbstractSmartList<T, _ListData, AbstractLinkedList<T> >::operator=;
};

}
#endif //ABSTRACTSMARTLINKEDLIST_H
