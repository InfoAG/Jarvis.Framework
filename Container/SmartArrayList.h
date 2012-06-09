#ifndef SMARTARRAYLIST_H
#define SMARTARRAYLIST_H

#include "ArrayListData.h"
#include "AbstractSmartList.h"

namespace CAS {

template <class T>
class SmartArrayList : public AbstractSmartList<T, ArrayListData<T> >
{

};

}

#endif //SMARTARRAYLIST_H
