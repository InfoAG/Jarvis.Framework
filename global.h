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

template <class T, class U>
bool equalOperands(const std::vector<T> &first, const std::vector<U> &second)
{
    typedef std::vector<typename U::pointer> OperandRefs;
    bool deleted;
    if (second.size() == first.size()) {
        OperandRefs spareSecondOps;
        for (const auto &operand : second) spareSecondOps.emplace_back(operand.get());
        for (const auto &firstItem : first){
            deleted = false;
            for (typename OperandRefs::iterator secondIt = spareSecondOps.begin(); secondIt != spareSecondOps.end(); ++secondIt) {
                if (firstItem->equals(*secondIt)) {
                    spareSecondOps.erase(secondIt);
                    deleted = true;
                    break;
                }
            }
            if (! deleted) return false;
        }
        return true;
    } else return false;
}

#endif //GLOBAL_H
