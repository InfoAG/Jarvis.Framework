#ifndef LIST_H
#define LIST_H

#include "Container.h"
#include <iostream>

/** @brief List class implemented as doubly linked list with nodewise COW.
  *
  * Optimized for copying of lists with large elements, insert / remove.
  * Suboptimal for small elements and random access.
  *
  * @author Alexander Schlüter
  */

//! A list node.
template <class T>
struct AbstractNode
{
    AbstractNode *previous; /**< Pointer to previous node in list. */
    AbstractNode *next; /**< Pointer to next node in list. */

    /** Copy constructor.
      * @param other Node to copy.
      * @param previous Pointer to previous node.
      * @param next Pointer to next node.
      */
    //inline Node(const Node &other, Node *previous = 0, Node *next = 0) : data(other.data->copy()), previous(previous), next(next) {};
    /** Copy constructor.
      * @param item Item to store.
      * @param previous Pointer to previous node.
      * @param next Pointer to next node.
      */
    inline AbstractNode(AbstractNode *previous = 0, AbstractNode *next = 0) : previous(previous), next(next) {};
    virtual AbstractNode *copy(AbstractNode *previous = 0, AbstractNode *next = 0) const = 0;
    /** Destructor.
      * @see release()
      */
    //inline ~AbstractNode() { data->release(); };

    /**
      * @return Returns a reference to the item.
      */
    virtual T &getItem() = 0;
};

template <class T>
class AbstractList : Container
{
private:
    //virtual Node *getLast() const = 0;

    //! Abstract base class for list iterators.
    class BaseIterator
    {
    private:
        const AbstractList *baseList; /**< Pointer to the list this iterator is based on. */

    protected:
        AbstractNode<T> *target; /**< Pointer to targeted node.*/

    public:
        /** Constructor.
          * @param target Pointer to target node.
          * @param baseList Pointer to base list.
          */
        inline BaseIterator(AbstractNode<T> *target = 0, const AbstractList  *baseList = 0) : target(target), baseList(baseList) {};
        /** Copy constructor.
          * @param other Reference of the list to copy.
          */
        inline BaseIterator(const BaseIterator &other) : target(other.target), baseList(other.baseList) {};

        inline BaseIterator &operator++() { target = target->next; return *this; };
        inline BaseIterator operator++(int) { target = target->next; return BaseIterator(target->previous, baseList); };
        inline BaseIterator &operator--();
        inline BaseIterator operator--(int);
        inline bool operator==(const BaseIterator &other) const { return (target == other.target && baseList == other.baseList); };
        inline bool operator!=(const BaseIterator &other) const { return ! (*this == other); };
        inline BaseIterator operator+(int n) const;
        inline BaseIterator operator-(int n) const { return operator+(-n); };
        inline BaseIterator &operator+=(int n) { return *this = *this + n; };
        inline BaseIterator &operator-=(int n) { return *this = *this - n; };

        const AbstractNode<T> * const getNode() const { return target; };
        const AbstractList * const getBaseList() const { return baseList; };
    };

public:
    //! List iterator.
    class iterator : public BaseIterator
    {
    public:
        inline iterator(AbstractNode<T> *target = 0, const AbstractList *baseList = 0) : BaseIterator(target, baseList) {};
        inline iterator(const BaseIterator &other) : BaseIterator(other) {};

        inline T &operator*() { return BaseIterator::target->getItem(); };
    };

    //! Const list iterator.
    class const_iterator : public BaseIterator
    {
    public:
        inline const_iterator(AbstractNode<T> *target = 0, const AbstractList *baseList = 0) : BaseIterator(target, baseList) {};
        inline const_iterator(const BaseIterator &other) : BaseIterator(other) {};

        inline const T &operator*() { return BaseIterator::target->getItem(); };

    };

    inline AbstractList() {};
    //AbstractList(const AbstractList<T> &other);

    /** Append one item to list.
      * @param item The item to append.
      */
    virtual void append(const T &item) = 0;
    /** Prepend one item to list.
      * @param item The item to prepend.
      */
    virtual void prepend(const T &item) = 0;
    /** Insert one item into list.
      * @param item The item to insert.
      * @param pos The position for the new item.
      */
    virtual void insert(const T &item, unsigned int pos) = 0;
    /** Remove one item from list.
      * @param pos Position of the item to remove.
      */
    virtual void remove(unsigned int pos) = 0;
    /** Delete all list items. */
    virtual void clear() = 0;

    /** @return Returns an iterator to the first item of the list.  */
    virtual iterator begin() = 0;
    /** @return Returns a const_iterator to the first item of the list.  */
    virtual const_iterator begin() const = 0;
    /** @return Returns an iterator pointing after the last item in the list.  */
    virtual iterator end() = 0;
    /** @return Returns a const_iterator pointing after the last item in the list.  */
    virtual const_iterator end() const = 0;
    /** Access one element based on its position.
      * @param pos The position to access.
      * @return A reference to the item.
      */
    virtual const T &at(unsigned int pos) const = 0;
    /** @return Returns true if the list is empty. */
    virtual bool isEmpty() const = 0;
    /** @return The list's size.*/
    virtual unsigned int size() const = 0;

    /*
    bool operator==(const AbstractList &other) const;
    bool operator!=(const AbstractList &other) const;
    AbstractList operator+(const T &item) const;
    AbstractList operator+(const AbstractList &other) const;
    AbstractList &operator+=(const T &item);
    AbstractList &operator+=(const AbstractList &other);
    T &operator[](unsigned int pos) const= 0;
    */
};

template <class T>
struct NaiveNode : public AbstractNode<T>
{
    T item;

    inline NaiveNode(const T &item, AbstractNode *previous = 0, AbstractNode *next = 0) : item(item), AbstractNode(previous, next) {};
    inline NaiveNode(const NaiveNode &other, AbstractNode *previous = 0, AbstractNode *next = 0) : item(other.item), AbstractNode(previous, next) {};
    virtual inline NaiveNode *copy(AbstractNode *previous = 0, AbstractNode *next = 0) const { return new NaiveNode(*this, previous, next); };

    virtual inline T &getItem() { return item; };
};

template <class T, class _Node = NaiveNode<T> >
class List : public AbstractList<T>
{
private:
    AbstractNode<T> *first; /**< Pointer to first node in list.*/
    AbstractNode<T> *last; /**< Pointer to last node in list.*/
    unsigned int _size; /**< List size.*/

    //virtual AbstractNode *getLast() const { return last; };

public:
    inline List() : first(0), last(0), _size(0) {};
    List(const List &other);

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

    bool operator==(const List &other) const;
    inline bool operator!=(const List &other) const { return ! (*this == other); };
    inline List operator+(const T &item) const { List result(*this); result.append(item); return result; };
    inline List operator+(const List &other) const { List result(*this); result += other; return result; };
    inline List &operator+=(const T &item) { append(item); };
    List &operator+=(const List &other);
    T &operator[](unsigned int pos) { iterator it(this->begin()); while (pos--) ++it; return *it; };
};

template <class T>
class AbstractListData //: public AbstractList<T>
{
protected:
    unsigned int refcount;

public:
    inline AbstractListData() : refcount(1) {};

    virtual inline AbstractListData *copy() { refcount++; return this; };
    void release();

    virtual AbstractListData *detach() = 0;
};

template <class T>
class SmartListData : public List<T, NaiveNode<T> >, public AbstractListData<T>
{
public:
    virtual inline SmartListData *copy() { refcount++; return this; };
    virtual SmartListData *detach();
};

template <class T, class _ListData>
class AbstractSmartList : public AbstractList<T>
{
private:
    _ListData *listData;

    inline void detach() { listData = listData->detach(); };
    //virtual AbstractNode *getLast() const { return listData->getLast(); };

public:
    inline AbstractSmartList() : listData(new _ListData) {};
    inline AbstractSmartList(const AbstractSmartList &other) : listData(other.listData->copy()) {};

    virtual inline void append(const T &item) { detach(); listData->append(item); };
    virtual inline void prepend(const T &item){ detach(); listData->prepend(item); };
    virtual inline void insert(const T &item, unsigned int pos){ detach(); listData->insert(item, pos); };
    virtual inline void remove(unsigned int pos){ detach(); listData->remove(pos); };
    virtual inline void clear() { detach(); listData->clear(); };

    virtual inline iterator begin() { return listData->begin(); };
    virtual inline const_iterator begin() const { return listData->begin(); };
    virtual inline iterator end() { return listData->end(); };
    virtual inline const_iterator end() const { return listData->end(); };
    virtual inline const T &at(unsigned int pos) const { return listData->at(pos); };
    virtual inline bool isEmpty() const { return listData->isEmpty(); };
    virtual inline unsigned int size() const { return listData->size(); };

    inline bool operator==(const AbstractSmartList &other) const { return *listData == other.listData; };
    inline bool operator!=(const AbstractSmartList &other) const { return ! (*this == other); };
    inline AbstractSmartList operator+(const T &item) const { AbstractSmartList result(*this); result.append(item); return result; };
    inline AbstractSmartList operator+(const AbstractSmartList &other) const { AbstractSmartList result(*this); result += other; return result; };
    inline AbstractSmartList &operator+=(const T &item) { append(item); };
    inline AbstractSmartList &operator+=(const AbstractSmartList &other) { detach(); *listData += *(other.listData); return *this; };
    inline T &operator[](unsigned int pos) { iterator it(this->begin()); while (pos--) ++it; return *it; };
};

template <class T>
class SmartList : public AbstractSmartList<T, SmartListData<T> >
{

};

template <class T>
struct SmartNode : AbstractNode<T>
{
    //! Smart node data for COW.
    class NodeData
    {
    private:
        T item; /**< Actual item data. */
        unsigned int refcount; /**< Number of nodes referencing this data. */

    public:
        /** Constructor.
          * @param item as the item to encapsulate.
          */
        inline NodeData(const T &item) : item(item), refcount(1) {};
        /** Adds a reference for a new node.
          * @return A pointer to this.
          * @see release()
          */
        inline NodeData *copy() { refcount++; return this; };
        /** Removes a reference and deletes when appropriate.
          * @see copy()
          */
        inline void release() { if (--refcount == 0) delete this; };
        inline NodeData *detach();

        inline T &getItem() { return item; };
    };

    NodeData *data; /**< Pointer to the NodeData object containing item data.*/

    inline SmartNode(const SmartNode &other, AbstractNode *previous = 0, AbstractNode *next = 0) : data(other.data->copy()), AbstractNode(previous, next) {};
    inline SmartNode(const T &item, AbstractNode *previous = 0, AbstractNode *next = 0) : data(new NodeData(item)), AbstractNode(previous, next) {};
    virtual inline SmartNode *copy(AbstractNode *previous = 0, AbstractNode *next = 0) const { return new SmartNode(*this, previous, next); };

    virtual inline T &getItem() { data = data->detach(); return data->getItem(); };
};

template <class T>
class RepetitiveListData : public AbstractListData<T>, public List<T, SmartNode<T> >
{
public:
    virtual inline RepetitiveListData *copy() { refcount++; return this; };
    virtual RepetitiveListData *detach();
};

template <class T>
class RepetitiveList : public AbstractSmartList<T, RepetitiveListData<T> >
{

};

#include "List.cpp"

#endif //LIST_H
