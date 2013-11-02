#ifndef DICTBENCODENODE_H
#define DICTBENCODENODE_H

#include "BencodeNode.h"

#include <QMap>
#include <QString>
#include <QSharedPointer>

class DictBencodeNode : public BencodeNode
{
public:
    DictBencodeNode(const QMap<QString, QSharedPointer<BencodeNode> >& dict = QMap<QString, QSharedPointer<BencodeNode> >());

    const QMap<QString, QSharedPointer<BencodeNode> >& dict() const;
    void setDict(const QMap<QString, QSharedPointer<BencodeNode> >& dict);

    //pure-virtual from BencodeNode
    virtual void accept(BencodeNodeVisitor * visitor);

private:
    QMap<QString, QSharedPointer<BencodeNode> > _dict;
};

#endif // DICTBENCODENODE_H
