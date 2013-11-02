#include "BencodeNodeVisitor.h"

#include <QtDebug>

BencodeNodeVisitor::BencodeNodeVisitor()
{
}

BencodeNodeVisitor::~BencodeNodeVisitor()
{
}

void BencodeNodeVisitor::visit(IntegerBencodeNode *node)
{
    qDebug() << "Int:" << node->num();
}

void BencodeNodeVisitor::visit(ByteStringBencodeNode *node)
{
    qDebug() << "Byte String:" << node->byteString();
}

void BencodeNodeVisitor::visit(ListBencodeNode *node)
{
    qDebug() << "List ( size" << node->elements().count() << "):";
}

void BencodeNodeVisitor::visit(DictBencodeNode *node)
{
    qDebug() << "Dict ( size" << node->dict().count() << "):";
}
