#ifndef DICTBENCODENODE_H
#define DICTBENCODENODE_H

#include "BencodeNode.h"
#include "ByteStringBencodeNode.h"

#include <QMap>
#include <QString>
#include <QSharedPointer>

class DictBencodeNode : public BencodeNode
{
public:
    DictBencodeNode(const QMap<QSharedPointer<ByteStringBencodeNode>, QSharedPointer<BencodeNode> >& dict = QMap<QSharedPointer<ByteStringBencodeNode>, QSharedPointer<BencodeNode> >());

    const QMap<QSharedPointer<ByteStringBencodeNode>, QSharedPointer<BencodeNode> >& dict() const;
    void setDict(const QMap<QSharedPointer<ByteStringBencodeNode>, QSharedPointer<BencodeNode> > &dict);

    //pure-virtual from BencodeNode
    virtual void accept(BencodeNodeVisitor * visitor);

private:
    QMap<QSharedPointer<ByteStringBencodeNode>, QSharedPointer<BencodeNode> > _dict;
};

#endif // DICTBENCODENODE_H
