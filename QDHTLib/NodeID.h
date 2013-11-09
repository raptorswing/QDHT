#ifndef NODEID_H
#define NODEID_H

#include <QByteArray>

#include "qdhtlib_global.h"

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

private:
    QByteArray _id;
};

uint qHash(const NodeID& node);

#endif // NODEID_H
