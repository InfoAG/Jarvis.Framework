#ifndef REPETITIVELIST_H
#define REPETITIVELIST_H

#include "RepetitiveLinkedList.h"

/** Alias for RepetitiveLinkedList (no template typedefs in C++)
  * @author Alexander Schl�ter
  */
template <class T>
class RepetitiveList : public RepetitiveLinkedList<T>
{

};

#endif //REPETITIVELIST_H
