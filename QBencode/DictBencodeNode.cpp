#include "DictBencodeNode.h"

#include "BencodeNodeVisitor.h"

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

//pure-virtual from BencodeNode
void DictBencodeNode::accept(BencodeNodeVisitor *visitor)
{
    const bool doTraversal = visitor->preVisit(this);

    if (doTraversal)
    {
        foreach(const QSharedPointer<BencodeNode>& child, _dict)
            child->accept(visitor);
    }

    visitor->postVisit(this);
}
