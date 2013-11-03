#include "DictBencodeNode.h"

#include "BencodeNodeVisitor.h"

DictBencodeNode::DictBencodeNode(const QMap<QSharedPointer<ByteStringBencodeNode>, QSharedPointer<BencodeNode> > &dict) :
    _dict(dict)
{
}

const QMap<QSharedPointer<ByteStringBencodeNode>, QSharedPointer<BencodeNode> > &DictBencodeNode::dict() const
{
    return _dict;
}

void DictBencodeNode::setDict(const QMap<QSharedPointer<ByteStringBencodeNode>, QSharedPointer<BencodeNode> > &dict)
{
    _dict = dict;
}

void DictBencodeNode::insert(const QSharedPointer<ByteStringBencodeNode> &key, const QSharedPointer<BencodeNode> &value)
{
    _dict.insert(key, value);
}

void DictBencodeNode::insert(const QString &key, const QSharedPointer<BencodeNode> &value)
{
    QByteArray bKey;
    bKey += key;
    _dict.insert(QSharedPointer<ByteStringBencodeNode>(new ByteStringBencodeNode(bKey)),
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
        foreach(const QSharedPointer<ByteStringBencodeNode>& keyNode, _dict.keys())
        {
            keyNode->accept(visitor);
            _dict.value(keyNode)->accept(visitor);
        }
    }

    visitor->postVisit(this);
}
