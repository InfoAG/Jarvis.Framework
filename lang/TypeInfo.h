#ifndef TYPEINFO_H
#define TYPEINFO_H

#include "global.h"
#include "exception/FatalTypeException.h"

namespace CAS {

class TypeInfo
{
public:
    enum StatementType {
        NUMBER = 1,
        BOOL = 2,
        VECTOR = 4,
        MATRIX = 8,
        VOID = 16,
        LIST
    };

private:
    StatementType type;
    std::unique_ptr<TypeInfo> next;

public:
    static TypeInfo fromString(const std::string &str);

    TypeInfo() : type(VOID) {}
    TypeInfo(const TypeInfo &other) : type(other.type) { if (other.next != nullptr) next = make_unique<TypeInfo>(*(other.next)); }
    TypeInfo(StatementType type) : type(type) {}
    TypeInfo(StatementType type, TypeInfo next) : type(type), next(make_unique<TypeInfo>(std::move(next))) {}

    std::string toString() const;
    TypeInfo *getNext() const { return next.get(); }

    TypeInfo &operator=(const TypeInfo &other) { type = other.type; if (other.next == nullptr) next.reset(); else next = make_unique<TypeInfo>(*(other.next)); return *this; }
    TypeInfo &operator=(StatementType otherType) { type = otherType; next.reset(); return *this; }

    bool operator==(const TypeInfo &other) const { return type == other.type && ((next == nullptr && other.next == nullptr) || (next != nullptr && other.next != nullptr && *next == *(other.next))); }
    bool operator!=(const TypeInfo &other) const { return ! (*this == other); }
    bool operator==(StatementType otherType) const { return type == otherType; }
    bool operator!=(StatementType otherType) const { return type != otherType; }
    bool operator<(const TypeInfo &other) const { if (type == other.type) return next != nullptr && other.next != nullptr && *next < *(other.next); else return type < other.type; }
};

}

#endif // TYPEINFO_H
