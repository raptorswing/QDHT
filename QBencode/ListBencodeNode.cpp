#include "ListBencodeNode.h"

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
