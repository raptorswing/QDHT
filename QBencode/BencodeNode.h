#ifndef BENCODENODE_H
#define BENCODENODE_H

#include "qbencode_global.h"

class BencodeNodeVisitor;

class QBENCODESHARED_EXPORT BencodeNode
{
public:
    enum BencodeNodeType
    {
        Integer,
        ByteString,
        List,
        Dictionary
    };

public:
    BencodeNode();
    virtual ~BencodeNode();

    virtual void accept(BencodeNodeVisitor * visitor) =0;
};

#endif // BENCODENODE_H
