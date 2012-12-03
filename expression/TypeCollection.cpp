#include "TypeCollection.h"

namespace CAS {

bool TypeCollection::contains(const TypeInfo &ti) const
{
    if (ti == TypeInfo::LIST) {
        if (std::find(types.cbegin(), types.cend(), ti) == types.cend()) {
            if (listElementTypes.empty()) return false;
            else {
                const TypeInfo *elT = ti.getNext();
                while (*elT == TypeInfo::LIST) elT = elT->getNext();
                return std::find(listElementTypes.cbegin(), listElementTypes.cend(), *elT) != listElementTypes.cend();
            }
        } else return true;
    } else return std::find(types.cbegin(), types.cend(), ti) != types.cend();
}

TypeCollection TypeCollection::flattenToElements() const
{
    std::set<TypeInfo> resultTs;
    for (const auto &t : types)
        if (t == TypeInfo::LIST) resultTs.insert(*(t.getNext()));
    for (const auto &let : listElementTypes) resultTs.insert(let);
    return {std::move(resultTs), listElementTypes};
}

TypeCollection TypeCollection::all()
{
    TypeCollection result{{TypeInfo::NUMBER, TypeInfo::BOOL, TypeInfo::VECTOR, TypeInfo::MATRIX, TypeInfo::VOID}, {TypeInfo::NUMBER, TypeInfo::BOOL, TypeInfo::VECTOR, TypeInfo::MATRIX, TypeInfo::VOID}};
    return result;
}

}
