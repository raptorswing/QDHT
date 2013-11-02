#include "IntegerBencodeNode.h"

#include <QtDebug>

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
