template <class T>
typename SmartNode<T>::NodeData *SmartNode<T>::NodeData::detach()
{
    if (refcount > 1) {
        refcount--;
        return new NodeData(item);
    } else return this;
}
