#ifndef BYTESTRINGBENCODENODE_H
#define BYTESTRINGBENCODENODE_H

#include "BencodeNode.h"

#include <QByteArray>

class ByteStringBencodeNode : public BencodeNode
{
public:
    ByteStringBencodeNode(const QByteArray& byteString);

    const QByteArray& byteString() const;
    void setByteString(const QByteArray& byteString);

    //pure-virtual from BencodeNode
    virtual void accept(BencodeNodeVisitor * visitor);


private:
    QByteArray _byteString;
};

#endif // BYTESTRINGBENCODENODE_H
