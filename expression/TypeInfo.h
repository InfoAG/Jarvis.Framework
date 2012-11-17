#ifndef TYPEINFO_H
#define TYPEINFO_H

#include "global.h"

namespace CAS {

struct TypeInfo
{
    enum ExpressionType {
        NUMBER,
        LIST,
        BOOL,
        VECTOR,
        VOID
    } type;
    std::unique_ptr<TypeInfo> next;

    static TypeInfo fromString(const std::string &str);

    TypeInfo() {}
    TypeInfo(const TypeInfo &other) : type(other.type) { if (other.next != nullptr) next = make_unique<TypeInfo>(*(other.next)); }
    TypeInfo(ExpressionType type) : type(type) {}
    TypeInfo(ExpressionType type, TypeInfo next) : type(type), next(make_unique<TypeInfo>(std::move(next))) {}

    std::string toString() const;
    TypeInfo getNext() const { return *next; }

    TypeInfo &operator=(const TypeInfo &other) { type = other.type; if (other.next == nullptr) next.reset(); else next = make_unique<TypeInfo>(*(other.next)); return *this; }
    TypeInfo &operator=(ExpressionType otherType) { type = otherType; next.reset(); return *this; }

    bool operator==(const TypeInfo &other) const { return type == other.type && ((next == nullptr && other.next == nullptr) || (next != nullptr && other.next != nullptr && *next == *(other.next))); }
    bool operator!=(const TypeInfo &other) const { return ! (*this == other); }
    bool operator==(ExpressionType otherType) const { return type == otherType; }
    bool operator!=(ExpressionType otherType) const { return type != otherType; }
    bool operator<(const TypeInfo &other) const { if (type == other.type) return next != nullptr && other.next != nullptr && *next < *(other.next); else return type < other.type; }
};

}

#endif // TYPEINFO_H
