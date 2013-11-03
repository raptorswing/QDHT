#ifndef BENCODENODE_H
#define BENCODENODE_H

#include "qbencode_global.h"

class BencodeNodeVisitor;

class QBENCODESHARED_EXPORT BencodeNode
{
public:
    enum BencodeNodeType
    {
        IntegerNodeType,
        ByteStringNodeType,
        ListNodeType,
        DictNodeType
    };

public:
    BencodeNode();
    virtual ~BencodeNode();

    virtual void accept(BencodeNodeVisitor * visitor) =0;

    virtual BencodeNodeType type() const =0;
};

#endif // BENCODENODE_H
