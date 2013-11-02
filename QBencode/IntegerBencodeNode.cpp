#include "IntegerBencodeNode.h"

#include <QtDebug>

#include "BencodeNodeVisitor.h"

IntegerBencodeNode::IntegerBencodeNode(qint64 num) :
    _num(num)
{
}

qint64 IntegerBencodeNode::num() const
{
    return _num;
}

void IntegerBencodeNode::setNum(qint64 num)
{
    _num = num;
}

//pure-virtual from BencodeNode
void IntegerBencodeNode::accept(BencodeNodeVisitor *visitor)
{
    visitor->preVisit(this);
    visitor->postVisit(this);
}
