#include "ByteStringBencodeNode.h"

ByteStringBencodeNode::ByteStringBencodeNode(const QByteArray &byteString) :
    _byteString(byteString)
{
}

const QByteArray &ByteStringBencodeNode::byteString() const
{
    return _byteString;
}

void ByteStringBencodeNode::setByteString(const QByteArray &byteString)
{
    _byteString = byteString;
}
