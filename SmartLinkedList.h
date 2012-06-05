#ifndef SMARTLINKEDLIST_H
#define SMARTLINKEDLIST_H

#include "AbstractSmartList.h"
#include "SmartLinkedListData.h"

/** @brief Doubly linked list with listwise COW
  *
  * This is probably the right list to use in most situations.
  * @author Alexander Schl�ter
  */
template <class T>
class SmartLinkedList : public AbstractSmartList<T, SmartLinkedListData<T> >
{

};


#endif //SMARTLINKEDLIST_H
