#ifndef BYTESTRINGBENCODENODE_H
#define BYTESTRINGBENCODENODE_H

#include "BencodeNode.h"
#include "qbencode_global.h"

#include <QByteArray>

class QBENCODESHARED_EXPORT ByteStringBencodeNode : public BencodeNode
{
public:
    ByteStringBencodeNode(const QByteArray& byteString);

    const QByteArray& byteString() const;
    void setByteString(const QByteArray& byteString);

    //pure-virtual from BencodeNode
    virtual void accept(BencodeNodeVisitor * visitor);

    //pure-virtual from BencodeNode
    virtual BencodeNodeType type() const;


private:
    QByteArray _byteString;
};

#endif // BYTESTRINGBENCODENODE_H
