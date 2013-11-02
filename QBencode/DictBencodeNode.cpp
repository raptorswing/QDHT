#include "DictBencodeNode.h"

DictBencodeNode::DictBencodeNode(const QMap<QString, QSharedPointer<BencodeNode> > &dict) :
    _dict(dict)
{
}

const QMap<QString, QSharedPointer<BencodeNode> > &DictBencodeNode::dict() const
{
    return _dict;
}

void DictBencodeNode::setDict(const QMap<QString, QSharedPointer<BencodeNode> > &dict)
{
    _dict = dict;
}
