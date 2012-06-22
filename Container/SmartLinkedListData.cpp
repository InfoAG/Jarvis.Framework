template <class T>
SmartLinkedListData<T> *SmartLinkedListData<T>::detach()
{
    if (refcount == 1) return this;
    else {
        refcount--;
        return new SmartLinkedListData(*this);
    }
}
