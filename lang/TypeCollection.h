#ifndef TYPECOLLECTION_H
#define TYPECOLLECTION_H

#include "TypeInfo.h"
#include "exception/FatalTypeException.h"
#include "exception/UndecidableTypeException.h"
#include <set>

namespace CAS {

class AbstractStatement;

struct TypeCollection
{
    std::set<TypeInfo> types;
    std::set<TypeInfo> listElementTypes;

    TypeCollection(std::set<TypeInfo> types) : types(std::move(types)) {}
    TypeCollection(std::set<TypeInfo> types, std::set<TypeInfo> listElementTypes) : types(std::move(types)), listElementTypes(std::move(listElementTypes)) {}

    bool contains(const TypeInfo &ti) const;
    void assertContains(const AbstractStatement &expr, const TypeInfo &ti) const;
    bool determinant() const { return types.size() == 1 && listElementTypes.empty(); }
    void assertDeterminant(const AbstractStatement &expr) const;
    void erase(const TypeInfo &ti) { types.erase(std::find(begin(types), end(types), ti)); }
    TypeCollection flattenToElements() const;

    static TypeCollection all();
    static TypeCollection allLists() { return TypeCollection({}, {TypeInfo::NUMBER, TypeInfo::BOOL, TypeInfo::VECTOR, TypeInfo::MATRIX, TypeInfo::VOID}); }
};

}

#endif // TYPECOLLECTION_H
