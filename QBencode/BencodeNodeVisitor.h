#ifndef BENCODENODEVISITOR_H
#define BENCODENODEVISITOR_H

#include "IntegerBencodeNode.h"
#include "ByteStringBencodeNode.h"
#include "ListBencodeNode.h"
#include "DictBencodeNode.h"

class BencodeNodeVisitor
{
public:
    BencodeNodeVisitor();
    virtual ~BencodeNodeVisitor();

    virtual void visit(IntegerBencodeNode * node);
    virtual void visit(ByteStringBencodeNode * node);
    virtual void visit(ListBencodeNode * node);
    virtual void visit(DictBencodeNode * node);
};

#endif // BENCODENODEVISITOR_H
