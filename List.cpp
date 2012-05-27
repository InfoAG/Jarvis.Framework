//#include "List.h"

template <class T>
List<T>::List(const List<T> &other) : size(other.getSize())
{
    if (getSize() != 0) {
        first = new Node(*(other.first)),
        last = first;
        for (Node *other_node = other.first->next; other_node != NULL; other_node = other_node->next) {
            last->next = new Node(*other_node, last);
            last = last->next;
        }
    }
}

template <class T>
void List<T>::append(const T &item)
{
    if (last == NULL) {
        last = new Node(item);
        first = last;
    } else {
        last->next = new Node(item, last);
        last = last->next;
        size++;
    }
}

template <class T>
void List<T>::prepend(const T &item)
{
    if (first == NULL)
    {
        first = new Node(item);
        last = first;
    } else {
        first->previous = new Node(item, NULL, first);
        first = first->previous;
        size++;
    }
}

template <class T>
T List<T>::at(unsigned int pos) const
{
    if (pos > size - 1) throw 0; //out_of_range
    else {
        List<T>::iterator it = this->begin();
        for (int i = 0; i < pos; i++)
            ++it;
        return *it;
    }
}

template <class T>
typename List<T>::Node::NodeData *List<T>::Node::NodeData::copy()
{
    refcount++;
    return this;
}

template <class T>
void List<T>::Node::NodeData::release()
{
    if (--refcount = 0) delete this;
}

template <class T>
void List<T>::clear()
{
    if (getSize() != 0) {
        for (Node *current_node = first->next; current_node != NULL; current_node = current_node->next)
            delete current_node->previous;
        delete last;
    }
    first = NULL;
    last = NULL;
    size = 0;
}
