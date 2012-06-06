#ifndef SMARTLINKEDLISTDATA_H
#define SMARTLINKEDLISTDATA_H

#include "List.h"
#include "NaiveNode.h"
#include "AbstractListData.h"

namespace CAS {

/** COW-enabled list data for a SmartLinkedList
  * @author Alexander Schlüter
  */
template <class T>
class SmartLinkedListData : public List<T, NaiveNode<T> >, public AbstractListData<T>
{
public:
    virtual inline SmartLinkedListData *copy() { refcount++; return this; };
    virtual SmartLinkedListData *detach();

    friend AbstractSmartList<T, SmartLinkedListData<T> >; //to access List::getLast() without making it public
};

#include "SmartLinkedListData.cpp"

}

#endif //SMARTLINKEDLISTDATA_H
