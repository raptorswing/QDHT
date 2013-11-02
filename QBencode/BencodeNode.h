#ifndef BENCODENODE_H
#define BENCODENODE_H

#include "qbencode_global.h"

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

    virtual void accept();
};

#endif // BENCODENODE_H
