#include "NodeID.h"

#include <QCryptographicHash>
#include <QString>
#include <QStringBuilder>

NodeID::NodeID()
{
}

NodeID::NodeID(const NodeID &other)
{
    _id = other.bytes();
}

NodeID::NodeID(const QByteArray &bytes)
{
    _id = bytes;
}

bool NodeID::isNull() const
{
    return _id.isNull();
}

const QByteArray &NodeID::bytes() const
{
    return _id;
}

const QString NodeID::hexBytes() const
{
    return this->bytes().toHex();
}

NodeID NodeID::GenerateRandom()
{
    const int a = qrand();
    const int b = qrand();
    const QString string = QString::number(a) % QString::number(b);
    return NodeID::GenerateFromString(string);
}

NodeID NodeID::GenerateFromBytes(const QByteArray &bytes)
{
    QCryptographicHash hasher(QCryptographicHash::Sha1);
    hasher.addData(bytes);

    return NodeID(hasher.result());
}

NodeID NodeID::GenerateFromString(const QString &string)
{
    QByteArray bytes;
    bytes += string;
    return NodeID::GenerateFromBytes(bytes);
}

bool NodeID::operator==(const NodeID &other) const
{
    return other.bytes() == this->bytes();
}

bool NodeID::operator!=(const NodeID &other) const
{
    return !(*this == other);
}

//non-member
uint qHash(const NodeID &node)
{
    return qHash(node.bytes());
}
