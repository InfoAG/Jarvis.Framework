#ifndef REPETITIVELINKEDLIST_H
#define REPETITIVELINKEDLIST_H

#include "AbstractSmartList.h"
#include "RepetitiveLinkedListData.h"

template <class T>
class RepetitiveLinkedList : public AbstractSmartList<T, RepetitiveLinkedListData<T> >
{

};

#endif //REPETITIVELINKEDLIST_H
