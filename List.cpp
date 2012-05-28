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
    if (last == 0) {
        last = new Node(item);
        first = last;
    } else {
        last->next = new Node(item, last);
        last = last->next;
    }
    size++;
}

template <class T>
void List<T>::prepend(const T &item)
{
    if (first == 0)
    {
        first = new Node(item);
        last = first;
    } else {
        first->previous = new Node(item, 0, first);
        first = first->previous;
    }
    size++;
}

template <class T>
const T &List<T>::at(unsigned int pos) const
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
void List<T>::clear()
{
    if (getSize() != 0) {
        for (Node *current_node = first->next; current_node != 0; current_node = current_node->next)
            delete current_node->previous;
        delete last;
    }
    first = 0;
    last = 0;
    size = 0;
}

template <class T>
void List<T>::insert(const T &item, unsigned int pos)
{
    if (pos == 0) prepend(item);
    else if (pos == getSize()) append(item);
    else if (pos > getSize()) throw 0; //out_of_range
    else {
        Node *previous_node = first;
        for (unsigned int i = 0; i < pos - 1; i++)
            previous_node = previous_node->next;
        previous_node->next->previous = new Node(item, previous_node, previous_node->next);
        previous_node->next = previous_node->next->previous;
        size++;
    }
}

template <class T>
void List<T>::remove(unsigned int pos)
{
    if (pos >= getSize()) throw 0; //out_of_range
    else {
        Node *target_node = first;
        for (unsigned int i = 0; i < pos; i++)
            target_node = target_node->next;
        if (target_node->previous != 0) target_node->previous->next = target_node->next;
        else first = target_node->next;
        if (target_node->next != 0) target_node->next->previous = target_node->previous;
        else last = target_node->previous;
        delete target_node;
        size--;
    }
}

template <class T>
T &List<T>::Node::getItem()
{
    if (data->refcount > 1) {
        NodeData *new_data = new NodeData(data->item);
        data->release();
        data = new_data;
    }
    return data->item;
}
