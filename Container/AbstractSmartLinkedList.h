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
private:
    typedef AbstractSmartList<T, _ListData, AbstractLinkedList<T> > _Inherited;

protected:
    virtual AbstractNode<T> *getFirst() const { return _Inherited::listData->getFirst(); };
    virtual AbstractNode<T> *getLast() const { return _Inherited::listData->getLast(); };

public:
    inline typename AbstractLinkedList<T>::iterator begin() { _Inherited::detach(); return typename AbstractLinkedList<T>::iterator(_Inherited::listData->getFirst(), this); };
    inline typename AbstractLinkedList<T>::const_iterator begin() const { return typename AbstractLinkedList<T>::const_iterator(_Inherited::listData->getFirst(), this); };
    inline typename AbstractLinkedList<T>::iterator end() { _Inherited::detach(); return typename AbstractLinkedList<T>::iterator(nullptr, this); };
    inline typename AbstractLinkedList<T>::const_iterator end() const { return typename AbstractLinkedList<T>::const_iterator(nullptr, this); };

    inline bool operator==(const AbstractSmartLinkedList &other) const { return *_Inherited::listData == *(other.listData); };
    inline bool operator!=(const AbstractSmartLinkedList &other) const { return ! (*this == other); };
    inline AbstractSmartLinkedList operator+(const T &item) const { AbstractSmartLinkedList result(*this); result.append(item); return result; };
    inline AbstractSmartLinkedList operator+(const AbstractSmartLinkedList &other) const { AbstractSmartLinkedList result(*this); result += other; return result; };
    inline AbstractSmartLinkedList &operator+=(const T &item) { append(item); };
    inline AbstractSmartLinkedList &operator+=(const AbstractSmartLinkedList &other) { _Inherited::detach(); *_Inherited::listData += *(other.listData); return *this; };
    inline T &operator[](unsigned int pos) { typename AbstractLinkedList<T>::iterator it(this->begin()); while (pos--) ++it; return *it; };
    using AbstractSmartList<T, _ListData, AbstractLinkedList<T> >::operator=;
};

}
#endif //ABSTRACTSMARTLINKEDLIST_H
