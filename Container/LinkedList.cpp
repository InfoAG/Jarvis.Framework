template <class T, class _Node>
LinkedList<T, _Node>::LinkedList(const LinkedList<T, _Node> &other) : _size(other.size())
{
    if (other.isEmpty()) {
        first = nullptr;
        last = nullptr;
    } else {
        first = new _Node(*(other.first));
        last = first;
        for (_Node *other_node = other.first->getNext(); other_node != 0; other_node = other_node->getNext()) {
            last->next = new _Node(*other_node, last);
            last = last->getNext();
        }
    }
}

template <class T, class _Node>
void LinkedList<T, _Node>::append(const T &item)
{
    if (last == 0) {
        last = new _Node(item);
        first = last;
    } else {
        last->next = new _Node(item, last);
        last = last->getNext();
    }
    _size++;
}

template <class T, class _Node>
void LinkedList<T, _Node>::append(T &&item)
{
    if (last == 0) {
        last = new _Node(std::forward<T>(item));
        first = last;
    } else {
        last->next = new _Node(std::forward<T>(item), last);
        last = last->getNext();
    }
    _size++;
}

template <class T, class _Node>
void LinkedList<T, _Node>::prepend(const T &item)
{
    if (first == 0)
    {
        first = new _Node(item);
        last = first;
    } else {
        first->previous = new _Node(item, 0, first);
        first = first->getPrevious();
    }
    _size++;
}

template <class T, class _Node>
void LinkedList<T, _Node>::prepend(T &&item)
{
    if (first == 0)
    {
        first = new _Node(std::forward<T>(item));
        last = first;
    } else {
        first->previous = new _Node(std::forward<T>(item), 0, first);
        first = first->getPrevious();
    }
    _size++;
}

template <class T, class _Node>
void LinkedList<T, _Node>::insert(const T &item, unsigned int pos)
{
    if (pos == 0) prepend(item);
    else if (pos == size()) append(item);
    else if (pos > size()) throw 0; //out_of_range
    else {
        AbstractNode<T> *previous_node = first;
        for (unsigned int i = 0; i < pos - 1; i++)
            previous_node = previous_node->getNext();
        previous_node->getNext()->previous = new _Node(item, previous_node, previous_node->getNext());
        previous_node->next = previous_node->getNext()->getPrevious();
        _size++;
    }
}

template <class T, class _Node>
void LinkedList<T, _Node>::insert(T &&item, unsigned int pos)
{
    if (pos == 0) prepend(std::forward<T>(item));
    else if (pos == size()) append(std::forward<T>(item));
    else if (pos > size()) throw 0; //out_of_range
    else {
        AbstractNode<T> *previous_node = first;
        for (unsigned int i = 0; i < pos - 1; i++)
            previous_node = previous_node->getNext();
        previous_node->getNext()->previous = new _Node(std::forward<T>(item), previous_node, previous_node->getNext());
        previous_node->next = previous_node->getNext()->getPrevious();
        _size++;
    }
}

template <class T, class _Node>
void LinkedList<T, _Node>::remove(unsigned int pos)
{
    if (pos >= size()) throw 0; //out_of_range
    else {
        _Node *target_node = first;
        for (unsigned int i = 0; i < pos; i++)
            target_node = target_node->getNext();
        if (target_node->getPrevious() != 0) target_node->getPrevious()->next = target_node->getNext();
        else first = target_node->getNext();
        if (target_node->getNext() != 0) target_node->getNext()->previous = target_node->getPrevious();
        else last = target_node->getPrevious();
        delete target_node;
        _size--;
    }
}

template <class T, class _Node>
void LinkedList<T, _Node>::clear()
{
    if (! isEmpty()) {
        for (AbstractNode<T> *current_node = first->getNext(); current_node != 0; current_node = current_node->getNext())
            delete current_node->getPrevious();
        delete last;
    }
    first = 0;
    last = 0;
    _size = 0;
}

template <class T, class _Node>
const T &LinkedList<T, _Node>::at(unsigned int pos) const
{
    if (pos > size() - 1) throw 0; //out_of_range
    else {
        typename AbstractLinkedList<T>::const_iterator it(this->begin());
        while (pos--) ++it;
        return *it;
    }

}

template <class T, class _Node>
bool LinkedList<T, _Node>::operator==(const LinkedList &other) const
{
    if (size() != other.size()) return false;
    else {
        for (typename AbstractLinkedList<T>::const_iterator it = begin(), it_other = other.begin(); it != end(); ++it, ++it_other)
            if (*it != *it_other) return false;
        return true;
    }
}

template <class T, class _Node>
LinkedList<T, _Node> &LinkedList<T, _Node>::operator +=(const LinkedList &other)
{
    if (! other.isEmpty()) {
        if (isEmpty()) {
            last = new _Node(*other.first);
            first = last;
        } else {
            last->next = new _Node(*other.first);
            last = last->getNext();
        }
        _Node *other_node = other.first->getNext();
        for (int i = other.size(); i > 1; i++) {
            last->next = new _Node(*other_node, last);
            last = last->getNext();
            other_node = other_node->getNext();
        }
        _size += other.size();
    }
    return *this;
}
