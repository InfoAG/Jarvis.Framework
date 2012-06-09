#ifndef REPETITIVELIST_H
#define REPETITIVELIST_H

#include "RepetitiveLinkedList.h"

namespace CAS {

/** Alias for RepetitiveLinkedList (no template typedefs in C++)
  * @author Alexander Schlüter
  */
template <class T>
class RepetitiveList : public RepetitiveLinkedList<T>
{

};

}

#endif //REPETITIVELIST_H
