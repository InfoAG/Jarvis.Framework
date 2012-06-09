template <class T>
ArrayListData<T> *ArrayListData<T>::detach()
{
    if (refcount == 1) return this;
    else {
        refcount--;
        return new ArrayListData(*this);
    }
}
