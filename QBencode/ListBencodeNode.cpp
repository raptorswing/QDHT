#include "ListBencodeNode.h"

ListBencodeNode::ListBencodeNode(const QList<BencodeNode *> &elements) :
    _elements(elements)
{
}

const QList<BencodeNode *> ListBencodeNode::elements() const
{
    return _elements;
}

void ListBencodeNode::setElements(const QList<BencodeNode *> &elements)
{
    _elements = elements;
}
