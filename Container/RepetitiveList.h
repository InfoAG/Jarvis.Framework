#ifndef REPETITIVELIST_H
#define REPETITIVELIST_H

#include "RepetitiveLinkedList.h"

namespace CAS {

/** Alias for RepetititveLinkedList (no template aliases for doxygen)
* @author Alexander Schlüter
*/

#ifndef DOXYGEN_PREPROCESSOR

template <class T>
using RepetitiveList = RepetitiveLinkedList<T>;

#else //DOXYGEN_PREPROCESSOR

template <class T>
class RepetitiveList : public RepetitiveLinkedList<T>
{
public:
    using RepetitiveLinkedList<T>::operator=;
};

#endif //DOXYGEN_PREPROCESSOR

}

#endif //REPETITIVELIST_H
