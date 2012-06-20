#ifndef REPETITIVELINKEDLISTDATA_H
#define REPETITIVELINKEDLISTDATA_H

#include "AbstractListData.h"
#include "LinkedList.h"
#include "SmartNode.h"
#include "AbstractSmartLinkedList.h"

namespace CAS {

/** COW-enabled list data for a RepetitiveLinkedList
  * @author Alexander Schlüter
  */
template <class T>
class RepetitiveLinkedListData : public AbstractListData<T>, public LinkedList<T, SmartNode<T> >
{
public:
    virtual inline RepetitiveLinkedListData *copy() { refcount++; return this; };
    virtual RepetitiveLinkedListData *detach();

    friend class AbstractSmartLinkedList<T, RepetitiveLinkedListData<T> >; //to access LinkedList::getLast() and LinkedList::getFirst() without making them public
};

#include "RepetitiveLinkedListData.cpp"

}

#endif //REPETITIVELINKEDLISTDATA_H
