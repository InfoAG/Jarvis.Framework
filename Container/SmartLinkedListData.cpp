template <class T>
SmartLinkedListData<T> *SmartLinkedListData<T>::detach()
{
    if (AbstractListData<T>::refcount == 1) return this;
    else {
        AbstractListData<T>::refcount--;
        return new SmartLinkedListData(*this);
    }
}
