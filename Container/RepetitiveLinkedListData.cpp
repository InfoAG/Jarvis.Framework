template <class T>
RepetitiveLinkedListData<T> *RepetitiveLinkedListData<T>::detach()
{
    if (refcount == 1) return this;
    else {
        refcount--;
        return new RepetitiveLinkedListData(*this);
    }
}
