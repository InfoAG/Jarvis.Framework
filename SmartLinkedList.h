#ifndef SMARTLINKEDLIST_H
#define SMARTLINKEDLIST_H

#include "AbstractSmartList.h"
#include "SmartLinkedListData.h"

template <class T>
class SmartList : public AbstractSmartList<T, SmartLinkedListData<T> >
{

};


#endif //SMARTLINKEDLIST_H
