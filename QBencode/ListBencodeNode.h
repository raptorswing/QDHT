#ifndef LISTBENCODENODE_H
#define LISTBENCODENODE_H

#include "BencodeNode.h"

#include <QList>
#include <QSharedPointer>

class ListBencodeNode : public BencodeNode
{
public:
    ListBencodeNode(const QList<QSharedPointer<BencodeNode> >& elements = QList<QSharedPointer<BencodeNode> >());

    const QList<QSharedPointer<BencodeNode> > elements() const;
    void setElements(const QList<QSharedPointer<BencodeNode> >& elements);

    //pure-virtual from BencodeNode
    virtual void accept(BencodeNodeVisitor * visitor);

private:
    QList<QSharedPointer<BencodeNode> > _elements;
};

#endif // LISTBENCODENODE_H
