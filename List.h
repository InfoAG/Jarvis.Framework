#ifndef LIST_H
#define LIST_H

#include <cstdlib> //not here

template <class T>
class List
{
private:
    struct Node
    {
        struct NodeData
        {
            T item;
            unsigned int refcount;

            NodeData(const T &item) : item(item), refcount(1) {};

            NodeData *copy();
            void release();
        };

        NodeData *data;
        Node *previous;
        Node *next;

        Node(const Node &other, Node *previous = NULL, Node *next = NULL) : data(other.data->copy()), previous(previous), next(next) {};
        Node(const T &item, Node *previous = NULL, Node *next = NULL) : data(new NodeData(item)), previous(previous), next(next) {};
        ~Node() { data->release(); };
    };

    class iterator
    {
    private:
        Node *item;

    public:

    };

    Node *first;
    Node *last;
    unsigned int size;

public:
    List() : first(NULL), last(NULL), size(0) {};
    List(const List<T> &other);

    void append(const T &item);
    void prepend(const T &item);
    void insert(const T &item, unsigned int before_pos);
    void remove(unsigned int pos);
    void clear();

    iterator begin() const;
    iterator end() const;
    T at(unsigned int pos) const;
    inline unsigned int getSize() const { return this->size; };
};

#include "List.cpp"

#endif //LIST_H
