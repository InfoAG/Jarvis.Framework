#ifndef ARRAYLISTDATA_H
#define ARRAYLISTDATA_H

#include "AbstractListData.h"
#include "ArrayList.h"

namespace CAS {

template <class T>
class ArrayListData : public AbstractListData<T>, public ArrayList<T>
{
public:
    virtual inline ArrayListData *copy() { AbstractListData<T>::refcount++; return this; };
    virtual ArrayListData *detach();
};

#include "ArrayListData.cpp"

}

#endif //ARRAYLISTDATA_H
