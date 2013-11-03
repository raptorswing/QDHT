#include "DictBencodeNode.h"

#include "BencodeNodeVisitor.h"

DictBencodeNode::DictBencodeNode(const QMap<QByteArray, QSharedPointer<BencodeNode> > &dict) :
    _dict(dict)
{
}

const QMap<QByteArray, QSharedPointer<BencodeNode> > &DictBencodeNode::dict() const
{
    return _dict;
}

void DictBencodeNode::setDict(const QMap<QByteArray, QSharedPointer<BencodeNode> > &dict)
{
    _dict = dict;
}

void DictBencodeNode::insert(const QString &key, const QSharedPointer<BencodeNode> &value)
{
    QByteArray bKey;
    bKey += key;
    _dict.insert(bKey,
                 value);
}

void DictBencodeNode::insert(const QString &key, const QByteArray &value)
{
    this->insert(key,
                 QSharedPointer<BencodeNode>(new ByteStringBencodeNode(value)));
}

//pure-virtual from BencodeNode
void DictBencodeNode::accept(BencodeNodeVisitor *visitor)
{
    const bool doTraversal = visitor->preVisit(this);

    if (doTraversal)
    {
        foreach(const QByteArray& keyVal, _dict.keys())
        {
            //Fakin' it
            QSharedPointer<ByteStringBencodeNode> temp(new ByteStringBencodeNode(keyVal));
            temp->accept(visitor);
            _dict.value(keyVal)->accept(visitor);
        }
    }

    visitor->postVisit(this);
}
