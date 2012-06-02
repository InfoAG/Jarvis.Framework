#ifndef ABSTRACTLISTDATA_H
#define ABSTRACTLISTDATA_H

template <class T>
class AbstractListData
{
protected:
    unsigned int refcount;

public:
    inline AbstractListData() : refcount(1) {};

    virtual inline AbstractListData *copy() { refcount++; return this; };
    void release();

    virtual AbstractListData *detach() = 0;
};

#endif //ABSTRACTLISTDATA_H
