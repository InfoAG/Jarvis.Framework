#ifndef GLOBAL_H
#define GLOBAL_H

#include <utility>
#include <algorithm>
#include <memory>

template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args )
{
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

#endif //GLOBAL_H
