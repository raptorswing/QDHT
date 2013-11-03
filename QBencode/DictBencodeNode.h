#ifndef DICTBENCODENODE_H
#define DICTBENCODENODE_H

#include "BencodeNode.h"
#include "ByteStringBencodeNode.h"
#include "qbencode_global.h"

#include <QMap>
#include <QString>
#include <QSharedPointer>

class QBENCODESHARED_EXPORT DictBencodeNode : public BencodeNode
{
public:
    DictBencodeNode(const QMap<QByteArray, QSharedPointer<BencodeNode> >& dict = QMap<QByteArray, QSharedPointer<BencodeNode> >());

    const QMap<QByteArray, QSharedPointer<BencodeNode> > &dict() const;
    void setDict(const QMap<QByteArray, QSharedPointer<BencodeNode> > &dict);

    void insert(const QString& key,
                const QSharedPointer<BencodeNode>& value);

    void insert(const QString& key,
                const QByteArray& value);

    //pure-virtual from BencodeNode
    virtual void accept(BencodeNodeVisitor * visitor);

private:
    QMap<QByteArray, QSharedPointer<BencodeNode> > _dict;
};

#endif // DICTBENCODENODE_H
