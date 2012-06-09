#ifndef SMARTLINKEDLISTDATA_H
#define SMARTLINKEDLISTDATA_H

#include "LinkedList.h"
#include "NaiveNode.h"
#include "AbstractListData.h"

namespace CAS {

/** COW-enabled list data for a SmartLinkedList
  * @author Alexander Schlüter
  */
template <class T>
class SmartLinkedListData : public LinkedList<T, NaiveNode<T> >, public AbstractListData<T>
{
public:
    virtual inline SmartLinkedListData *copy() { refcount++; return this; };
    virtual SmartLinkedListData *detach();

    friend AbstractSmartLinkedList<T, SmartLinkedListData<T> >; //to access List::getLast() and List::getFirst() without making them public
};

#include "SmartLinkedListData.cpp"

}

#endif //SMARTLINKEDLISTDATA_H
