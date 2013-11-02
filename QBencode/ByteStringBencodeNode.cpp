#include "ByteStringBencodeNode.h"

#include "BencodeNodeVisitor.h"

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

//pure-virtual from BencodeNode
void ByteStringBencodeNode::accept(BencodeNodeVisitor * visitor)
{
    visitor->preVisit(this);
    visitor->postVisit(this);
}
