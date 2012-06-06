template <class T>
typename AbstractList<T>::BaseIterator &AbstractList<T>::BaseIterator::operator--()
{
    if (target == 0) target = baseList->getLast();
    else target = target->previous;
    return *this;
}

template <class T>
typename AbstractList<T>::BaseIterator AbstractList<T>::BaseIterator::operator--(int)
{
    if (target == 0) target = baseList->getLast();
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
