#ifndef NODEID_H
#define NODEID_H

#include <QByteArray>
#include <QHash>

#include "qdhtlib_global.h"

#define TTMATH_NOASM
#include "ttmath/ttmath.h"
#ifdef TTMATH_PLATFORM64
#define NODEID_WORDS 3
#else
#define NODEID_WORDS 5
#endif

class QDHTLIBSHARED_EXPORT NodeID
{
public:
    NodeID();
    NodeID(const NodeID& other);
    NodeID(const QByteArray& bytes);

    bool isNull() const;

    const QByteArray& bytes() const;
    const QString hexBytes() const;

    static NodeID GenerateRandom();
    static NodeID GenerateFromBytes(const QByteArray& bytes);
    static NodeID GenerateFromString(const QString& string);

    bool operator==(const NodeID& other) const;
    bool operator!=(const NodeID& other) const;

    ttmath::UInt<NODEID_WORDS> toBigUint() const;

private:
    QByteArray _id;
};

uint qHash(const NodeID& node);

#endif // NODEID_H
