template <class T>
ArrayListData<T> *ArrayListData<T>::detach()
{
    if (AbstractListData<T>::refcount == 1) return this;
    else {
        AbstractListData<T>::refcount--;
        return new ArrayListData(*this);
    }
}
