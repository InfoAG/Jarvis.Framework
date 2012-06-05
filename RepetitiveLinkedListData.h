#ifndef REPETITIVELINKEDLISTDATA_H
#define REPETITIVELINKEDLISTDATA_H

#include "AbstractListData.h"
#include "List.h"
#include "SmartNode.h"

/** COW-enabled list data for a RepetitiveLinkedList
  * @author Alexander Schl�ter
  */
template <class T>
class RepetitiveLinkedListData : public AbstractListData<T>, public List<T, SmartNode<T> >
{
public:
    virtual inline RepetitiveLinkedListData *copy() { refcount++; return this; };
    virtual RepetitiveLinkedListData *detach();
};

#include "RepetitiveLinkedListData.cpp"

#endif //REPETITIVELINKEDLISTDATA_H
