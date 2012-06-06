#ifndef REPETITIVELINKEDLISTDATA_H
#define REPETITIVELINKEDLISTDATA_H

#include "AbstractListData.h"
#include "List.h"
#include "SmartNode.h"

namespace CAS {

/** COW-enabled list data for a RepetitiveLinkedList
  * @author Alexander Schlüter
  */
template <class T>
class RepetitiveLinkedListData : public AbstractListData<T>, public List<T, SmartNode<T> >
{
public:
    virtual inline RepetitiveLinkedListData *copy() { refcount++; return this; };
    virtual RepetitiveLinkedListData *detach();

    friend AbstractSmartList<T, RepetitiveLinkedListData<T> >; //to access List::getLast() without making it public
};

#include "RepetitiveLinkedListData.cpp"

}

#endif //REPETITIVELINKEDLISTDATA_H
