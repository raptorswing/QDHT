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

    virtual void visit(QSharedPointer<IntegerBencodeNode> node);
    virtual void visit(QSharedPointer<ByteStringBencodeNode> node);
    virtual void visit(QSharedPointer<ListBencodeNode> node);
    virtual void visit(QSharedPointer<DictBencodeNode> node);
};

#endif // BENCODENODEVISITOR_H
