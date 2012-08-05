template <class T>
typename AbstractLinkedList<T>::BaseIterator &AbstractLinkedList<T>::BaseIterator::operator--()
{
    if (target == 0) target = AbstractList<T>::BaseIterator::baseList->getLast();
    else target = target->previous;
    return *this;
}

template <class T>
typename AbstractLinkedList<T>::BaseIterator &AbstractLinkedList<T>::BaseIterator::operator--(int)
{
    BaseIterator result(*this);
    if (target == 0) target = AbstractList<T>::BaseIterator::baseList->getLast();
    else target = target->previous;
    return result;
}

template <class T>
typename AbstractLinkedList<T>::BaseIterator AbstractLinkedList<T>::BaseIterator::operator+(int n) const
{
    BaseIterator result(*this);
    if (n > 0)
        while (n--) ++result;
    else
        while (n++) --result;
    return result;
}
