template <class T>
ArrayList<T>::ArrayList(const ArrayList &other) : _size(other.size()), array(new T[other.size()]) //reserved
{
    for (int i = 0; i < size(); i++)
        array[i] = other.array[i];
}

template <class T>
void ArrayList<T>::append(const T &item)
{
    if (size() >= reserved) reserve(1);
    array[size()] = item;
    _size++;
}

template <class T>
void ArrayList<T>::prepend(const T &item)
{
    if (size() >= reserved) reserve(1);
    array[size()] = item;
    _size++;
}
