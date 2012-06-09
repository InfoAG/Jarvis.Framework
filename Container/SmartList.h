#ifndef SMARTLIST_H
#define SMARTLIST_H

#include "SmartLinkedList.h"

namespace CAS {

/** Alias for SmartLinkedList (no template typedefs in C++)
  * @author Alexander Schlüter
  */
template <class T>
class SmartList : public SmartLinkedList<T>
{

};

}

#endif //SMARTLIST_H
