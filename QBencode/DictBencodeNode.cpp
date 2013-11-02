#include "DictBencodeNode.h"

DictBencodeNode::DictBencodeNode(const QMap<QString, BencodeNode *> &dict) :
    _dict(dict)
{
}

const QMap<QString, BencodeNode *> &DictBencodeNode::dict() const
{
    return _dict;
}

void DictBencodeNode::setDict(const QMap<QString, BencodeNode *> &dict)
{
    _dict = dict;
}
