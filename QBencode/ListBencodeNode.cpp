#include "ListBencodeNode.h"

#include "BencodeNodeVisitor.h"

ListBencodeNode::ListBencodeNode(const QList<QSharedPointer<BencodeNode> > &elements) :
    _elements(elements)
{
}

const QList<QSharedPointer<BencodeNode> > ListBencodeNode::elements() const
{
    return _elements;
}

void ListBencodeNode::setElements(const QList<QSharedPointer<BencodeNode> > &elements)
{
    _elements = elements;
}

//pure-virtual from BencodeNode
void ListBencodeNode::accept(BencodeNodeVisitor *visitor)
{
    const bool doTraversal = visitor->preVisit(this);

    if (doTraversal)
    {
        foreach(const QSharedPointer<BencodeNode>& child, _elements)
            child->accept(visitor);
    }

    visitor->postVisit(this);
}

//pure-virtual from BencodeNode
BencodeNode::BencodeNodeType ListBencodeNode::type() const
{
    return ListNodeType;
}
