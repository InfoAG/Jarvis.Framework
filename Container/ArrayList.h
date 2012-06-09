#ifndef ARRAY_H
#define ARRAY_H

#include "AbstractList.h"

namespace CAS {

template <class T>
class ArrayList : public AbstractList<T>
{
private:
    T *array;
    unsigned int _size;
    unsigned int reserved;

public:
    inline ArrayList() : array(0), _size(0), reserved(0) {};
    inline ArrayList(const ArrayList &other);

    virtual void append(const T &item);
    virtual void prepend(const T &item);
    virtual void insert(const T &item, unsigned int pos);
    virtual void remove(unsigned int pos);
    virtual void clear();

    virtual inline iterator begin() { return iterator(first, this); };
    virtual inline const_iterator begin() const { return const_iterator(first, this); };
    virtual inline iterator end() { return iterator(0, this); };
    virtual inline const_iterator end() const { return const_iterator(0, this); };
    virtual const T &at(unsigned int pos) const;
    virtual inline bool isEmpty() const { return size() == 0; };
    virtual inline unsigned int size() const { return _size; };

    bool operator==(const ArrayList &other) const;
    inline bool operator!=(const ArrayList &other) const { return ! (*this == other); };
    inline ArrayList operator+(const T &item) const { List result(*this); result.append(item); return result; };
    inline ArrayList operator+(const ArrayList &other) const { List result(*this); result += other; return result; };
    inline ArrayList &operator+=(const T &item) { append(item); };
    ArrayList &operator+=(const ArrayList &other);
    T &operator[](unsigned int pos) { iterator it(this->begin()); while (pos--) ++it; return *it; };
};

#include "ArrayList.cpp"

}

#endif //ARRAY_H
