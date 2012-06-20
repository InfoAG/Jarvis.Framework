#ifndef REPETITIVELINKEDLIST_H
#define REPETITIVELINKEDLIST_H

#include "AbstractSmartList.h"
#include "RepetitiveLinkedListData.h"

namespace CAS {

/** @brief Doubly linked list with both listwise and nodewise COW
  *
  * Optimized for a high number of equal elements due to copying / appending
  * and / or large element types. Efficient when
  *
  * sizeof(T) >= -4 * (unique_items / nodes + 1) / (unique_items / nodes - 1)
  *
  * Overhead lies in the reference count of SmartNode::NodeData and the pointer to this data.
  * @author Alexander Schlüter
  */
template <class T>
class RepetitiveLinkedList : public AbstractSmartLinkedList<T, RepetitiveLinkedListData<T> >
{
public:
    using AbstractSmartLinkedList<T, RepetitiveLinkedListData<T> >::operator=;
};

}

#endif //REPETITIVELINKEDLIST_H
