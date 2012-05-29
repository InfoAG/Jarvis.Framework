//#include "List.h"

template <class T>
List<T>::List(const List<T> &other) : _size(other.size())
{
    if (! isEmpty()) {
        first = new Node(*(other.first)),
        last = first;
        for (Node *other_node = other.first->next; other_node != 0; other_node = other_node->next) {
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
    _size++;
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
    _size++;
}

template <class T>
const T &List<T>::at(unsigned int pos) const
{
    if (pos > size() - 1) throw 0; //out_of_range
    else return (*this)[pos];
}

template <class T>
void List<T>::clear()
{
    if (! isEmpty()) {
        for (Node *current_node = first->next; current_node != 0; current_node = current_node->next)
            delete current_node->previous;
        delete last;
    }
    first = 0;
    last = 0;
    _size = 0;
}

template <class T>
void List<T>::insert(const T &item, unsigned int pos)
{
    if (pos == 0) prepend(item);
    else if (pos == size()) append(item);
    else if (pos > size()) throw 0; //out_of_range
    else {
        Node *previous_node = first;
        for (unsigned int i = 0; i < pos - 1; i++)
            previous_node = previous_node->next;
        previous_node->next->previous = new Node(item, previous_node, previous_node->next);
        previous_node->next = previous_node->next->previous;
        _size++;
    }
}

template <class T>
void List<T>::remove(unsigned int pos)
{
    if (pos >= size()) throw 0; //out_of_range
    else {
        Node *target_node = first;
        for (unsigned int i = 0; i < pos; i++)
            target_node = target_node->next;
        if (target_node->previous != 0) target_node->previous->next = target_node->next;
        else first = target_node->next;
        if (target_node->next != 0) target_node->next->previous = target_node->previous;
        else last = target_node->previous;
        delete target_node;
        _size--;
    }
}

template <class T>
inline T &List<T>::operator[](unsigned int pos) const
{
    iterator it = this->begin();
    while (pos--) ++it;
    return *it;
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

template <class T>
typename List<T>::BaseIterator &List<T>::BaseIterator::operator--()
{
    if (target == 0) target = baseList->last;
    else target = target->previous;
    return *this;
}

template <class T>
typename List<T>::BaseIterator List<T>::BaseIterator::operator--(int)
{
    if (target == 0) target = baseList->last;
    else target = target->previous;
    return BaseIterator(target->next, baseList);
}

template <class T>
typename List<T>::BaseIterator List<T>::BaseIterator::operator+(int n) const
{
    BaseIterator result(*this);
    if (n > 0)
        while (n--) ++result;
    else
        while (n++) --result;
    return result;
}

template <class T>
bool List<T>::operator==(const List &other) const
{
    if (size() != other.size()) return false;
    else {
        for (const_BaseIterator it = begin(), it_other = other.begin(); it != end(); ++it, ++it_other)
            if (*it != *it_other) return false;
        return true;
    }
}

template <class T>
List<T> &List<T>::operator +=(const List &other)
{
    if (! other.isEmpty()) {
        if (isEmpty()) {
            last = new Node(*(other.first));
            first = last;
        } else {
            last->next = new Node(*(other.first));
            last = last->next;
        }
        for (Node *other_node = other.first->next; other_node != 0; other_node = other_node->next) {
            last->next = new Node(*other_node, last);
            last = last->next;
        }
        _size += other.size();
    }
    return *this;
}
