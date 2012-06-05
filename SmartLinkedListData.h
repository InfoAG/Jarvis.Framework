#ifndef SMARTLINKEDLISTDATA_H
#define SMARTLINKEDLISTDATA_H

#include "List.h"
#include "NaiveNode.h"
#include "AbstractListData.h"

/** COW-enabled list data for a SmartLinkedList
  * @author Alexander Schlüter
  */
template <class T>
class SmartLinkedListData : public List<T, NaiveNode<T> >, public AbstractListData<T>
{
public:
    virtual inline SmartLinkedListData *copy() { refcount++; return this; };
    virtual SmartLinkedListData *detach();
};

#include "SmartLinkedListData.cpp"

#endif //SMARTLINKEDLISTDATA_H
