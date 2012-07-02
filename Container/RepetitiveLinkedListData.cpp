template <class T>
RepetitiveLinkedListData<T> *RepetitiveLinkedListData<T>::detach()
{
    if (AbstractListData<T>::refcount == 1) return this;
    else {
        AbstractListData<T>::refcount--;
        return new RepetitiveLinkedListData(*this);
    }
}
