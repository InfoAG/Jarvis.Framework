#ifndef SMARTLIST_H
#define SMARTLIST_H

#include "SmartLinkedList.h"

namespace CAS {

/** Alias for SmartLinkedList (no template aliases for doxygen)
* @author Alexander Schlüter
*/

#ifndef DOXYGEN_PREPROCESSOR

template <class T>
using SmartList = SmartLinkedList<T>;

#else //DOXYGEN_PREPROCESSOR

template <class T>
class SmartList : public SmartLinkedList<T>
{
public:
    using SmartLinkedList<T>::operator=;
};

#endif //DOXYGEN_PREPROCESSOR

}

#endif //SMARTLIST_H
