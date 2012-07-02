#ifndef SMARTLINKEDLIST_H
#define SMARTLINKEDLIST_H

#include "AbstractSmartLinkedList.h"
#include "SmartLinkedListData.h"

namespace CAS {

/** @brief Doubly linked list with listwise COW
  *
  * This is probably the right list to use in most situations.
  * @author Alexander Schl�ter
  */

#ifndef DOXYGEN_PREPROCESSOR

template <class T>
using SmartLinkedList = AbstractSmartLinkedList<T, SmartLinkedListData<T> >;

#else //DOXYGEN_PREPROCESSOR

template <class T>
class SmartLinkedList : public AbstractSmartLinkedList<T, SmartLinkedListData<T> >
{
public:
    using AbstractSmartLinkedList<T, SmartLinkedListData<T> >::operator=;
};

#endif //DOXYGEN_PREPROCESSOR

}

#endif //SMARTLINKEDLIST_H
