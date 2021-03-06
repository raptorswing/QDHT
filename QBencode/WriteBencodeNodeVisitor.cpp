#include "WriteBencodeNodeVisitor.h"

WriteBencodeNodeVisitor::WriteBencodeNodeVisitor()
{
}

const QByteArray &WriteBencodeNodeVisitor::output() const
{
    return _output;
}

void WriteBencodeNodeVisitor::reset()
{
    _output = QByteArray();
}


bool WriteBencodeNodeVisitor::preVisit(IntegerBencodeNode *node)
{
    _output += "i" + QString::number(node->num()) + "e";
    return true;
}

bool WriteBencodeNodeVisitor::preVisit(ByteStringBencodeNode *node)
{
    _output += QString::number(node->byteString().length()) + ":";
    _output += node->byteString();
    return true;
}

bool WriteBencodeNodeVisitor::preVisit(ListBencodeNode *node)
{
    Q_UNUSED(node)
    _output += "l";
    return true;
}

bool WriteBencodeNodeVisitor::preVisit(DictBencodeNode *node)
{
    Q_UNUSED(node)
    _output += "d";
    return true;
}

//void WriteBencodeNodeVisitor::postVisit(IntegerBencodeNode *node)
//{

//}

//void WriteBencodeNodeVisitor::postVisit(ByteStringBencodeNode *node)
//{

//}

void WriteBencodeNodeVisitor::postVisit(ListBencodeNode *node)
{
    Q_UNUSED(node)
    _output += "e";
}

void WriteBencodeNodeVisitor::postVisit(DictBencodeNode *node)
{
    Q_UNUSED(node)
    _output += "e";
}
