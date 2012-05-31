template <class T, class _Node>
List<T, _Node>::List(const List<T, _Node> &other) : _size(other.size())
{
    if (! other.isEmpty()) {
        first = other.first->copy(),
        last = first;
        for (AbstractNode<T> *other_node = other.first->next; other_node != 0; other_node = other_node->next) {
            last->next = other_node->copy(last);
            last = last->next;
        }
    }
}

template <class T, class _Node>
void List<T, _Node>::append(const T &item)
{
    if (last == 0) {
        last = new _Node(item);
        first = last;
    } else {
        last->next = new _Node(item, last);
        last = last->next;
    }
    _size++;
}

template <class T, class _Node>
void List<T, _Node>::prepend(const T &item)
{
    if (first == 0)
    {
        first = new _Node(item);
        last = first;
    } else {
        first->previous = new _Node(item, 0, first);
        first = first->previous;
    }
    _size++;
}

template <class T, class _Node>
void List<T, _Node>::insert(const T &item, unsigned int pos)
{
    if (pos == 0) prepend(item);
    else if (pos == size()) append(item);
    else if (pos > size()) throw 0; //out_of_range
    else {
        AbstractNode<T> *previous_node = first;
        for (unsigned int i = 0; i < pos - 1; i++)
            previous_node = previous_node->next;
        previous_node->next->previous = new _Node(item, previous_node, previous_node->next);
        previous_node->next = previous_node->next->previous;
        _size++;
    }
}

template <class T, class _Node>
void List<T, _Node>::remove(unsigned int pos)
{
    if (pos >= size()) throw 0; //out_of_range
    else {
        AbstractNode<T> *target_node = first;
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

template <class T, class _Node>
void List<T, _Node>::clear()
{
    if (! isEmpty()) {
        for (AbstractNode<T> *current_node = first->next; current_node != 0; current_node = current_node->next)
            delete current_node->previous;
        delete last;
    }
    first = 0;
    last = 0;
    _size = 0;
}

template <class T, class _Node>
const T &List<T, _Node>::at(unsigned int pos) const
{
    if (pos > size() - 1) throw 0; //out_of_range
    else {
        iterator it(this->begin());
        while (pos--) ++it;
        return *it;
    }

}

template <class T, class _Node>
bool List<T, _Node>::operator==(const List &other) const
{
    if (size() != other.size()) return false;
    else {
        for (const_iterator it = begin(), it_other = other.begin(); it != end(); ++it, ++it_other)
            if (*it != *it_other) return false;
        return true;
    }
}

template <class T, class _Node>
List<T, _Node> &List<T, _Node>::operator +=(const List &other)
{
    if (! other.isEmpty()) {
        if (isEmpty()) {
            last = other.first->copy();
            first = last;
        } else {
            last->next = other.first->copy();
            last = last->next;
        }
        AbstractNode<T> *other_node = other.first->next;
        for (int i = other.size(); i > 1; i++) {
            last->next = other_node->copy(last);
            last = last->next;
            other_node = other_node->next;
        }
        _size += other.size();
    }
    return *this;
}

/*template <class T>
RepetitiveList<T, _Node>::RepetitiveList(const RepetitiveList<T, _Node> &other) : _size(other.size())
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
T &RepetitiveList<T, _Node>::Node::getItem()
{
    if (data->refcount > 1) {
        NodeData *new_data = new NodeData(data->item);
        data->release();
        data = new_data;
    }
    return data->item;
}
*/
template <class T>
typename AbstractList<T>::BaseIterator &AbstractList<T>::BaseIterator::operator--()
{
    if (target == 0) target = baseList->last;
    else target = target->previous;
    return *this;
}

template <class T>
typename AbstractList<T>::BaseIterator AbstractList<T>::BaseIterator::operator--(int)
{
    if (target == 0) target = baseList->last;
    else target = target->previous;
    return BaseIterator(target->next, baseList);
}

template <class T>
typename AbstractList<T>::BaseIterator AbstractList<T>::BaseIterator::operator+(int n) const
{
    BaseIterator result(*this);
    if (n > 0)
        while (n--) ++result;
    else
        while (n++) --result;
    return result;
}

template <class T>
SmartListData<T> *SmartListData<T>::detach()
{
    if (refcount == 1) return this;
    else {
        refcount--;
        return new SmartListData(*this);
    }
}

template <class T>
RepetitiveListData<T> *RepetitiveListData<T>::detach()
{
    if (refcount == 1) return this;
    else {
        refcount--;
        return new RepetitiveListData(*this);
    }
}

template <class T>
typename SmartNode<T>::NodeData *SmartNode<T>::NodeData::detach()
{
    if (refcount > 1) {
        refcount--;
        return new NodeData(item);
    } else return this;
}
